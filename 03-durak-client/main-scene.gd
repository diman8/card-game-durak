extends Node

var card = load("res://Card.scn")
var lcardid
var gl_lapl
var gl_vpl
var action=""
var server = StreamPeerTCP.new()
#var server_listener = Thread.new()
var players=[]
onready var pllist = get_node("GameList")

func _ready():
	get_node("Log").set_readonly(true)
	get_node("connect").show()
	get_node("connect").set_pos(OS.get_window_size()/2-get_node("connect").get_size()/2)
	#set_fixed_process(true)
	#get_hand()
	#draw_deck()


func _on_Connect_pressed():
	server.connect(get_node("connect/ip").get_text(), int(get_node("connect/port").get_text()))
	if (server.get_status() == 2):
		get_node("Log").insert_text_at_cursor("success connection to " + get_node("connect/ip").get_text() + ":" + get_node("connect/port").get_text() + "\n")
		get_node("connect").hide()
		server.put_data(get_node("connect/player_name").get_text().to_utf8())	
		get_node("PopupMenu 2").show()
		get_node("PopupMenu 2").set_pos(OS.get_window_size()/2-get_node("PopupMenu 2").get_size()/2)
	else:
		get_node("Log").insert_text_at_cursor("error on connecting to server\n")

func get_hand():
	#я хочу чтобы все карты помещались в 700px.
	#тогда отступы должны быть ограничены 600px
	var hand = get_node("hand")
	var size=6;
	var offset=600/(size+1)
	for i in range(1,size+1):
		var tmp = card.instance()
		hand.add_child(tmp)
		tmp.set_pos(Vector2(offset*i,0))
		tmp.face=i-1
		tmp.up=true
		tmp.movable=true

func draw_deck(size):
	var cards = get_node("Deck/cards")
	get_node("Deck/size").set_text(str(size))
	for a in cards.get_children():
		#cards.remove_child(a)
		a.queue_free()
	if size==0:
		get_node("Deck/size").hide()
		get_node("Deck/trump").hide()
		return
	elif size==1:
		get_node("Deck/trump").show()
		return
	else:
		get_node("Deck/trump").show()
		for i in range(0,size/4):
			var tmp = card.instance()
			cards.add_child(tmp)
			tmp.set_pos(Vector2(-i,-i))



func _on_Listener_timeout():
	if server.is_connected() && server.get_available_bytes() > 0:
		get_node("PopupMenu 2").hide()
		var data = server.get_string(server.get_available_bytes())
		var arr = separate_jsons(data)
		for x in arr:
			get_node("Log").insert_text_at_cursor(x + '\n')
			game_signal(x)
	get_node("Listener").start()

func game_signal(data):
	var dict = {}
	dict.parse_json(data)
	if dict["signal"]=="gameinfo":
		s_gameinfo(dict)
	elif dict["signal"]=="order":
		s_order(dict)
	elif dict["signal"]=="turna":
		s_turna(dict)
	elif dict["signal"]=="turnv":
		s_turnv(dict)
	elif dict["signal"]=="thrown":
		s_thrown(dict)
	elif dict["signal"]=="answer":
		s_answer(dict)
	elif dict["signal"]=="status":
		s_status(dict)
	elif dict["signal"]=="done":
		s_done(dict)
	elif dict["signal"]=="turnend":
		s_turnend()

func s_turnend():
	for i in get_node("Pairs").get_children():
		i.queue_free()

func s_turna(dict):
	if !dict.has("none"):
		var pairs = get_node("Pairs")
		var offset=80
		var tmp = card.instance()
		pairs.add_child(tmp)
		tmp.set_pos(Vector2(offset*(pairs.get_child_count()-1),0))
		tmp.face=dict["card"][0]
		tmp.suit=dict["card"][1]
		tmp.up=true
		players[dict["plid"]]["cards"]-=1
		update_pl_list()

func s_turnv(dict):
	if !dict.has("giveup"):
		var lpair = get_node("Pairs").get_child(get_node("Pairs").get_child_count()-1)
		var tmp = card.instance()
		lpair.add_child(tmp)
		tmp.set_pos(Vector2(20,20))
		tmp.face=dict["card"][0]
		tmp.suit=dict["card"][1]
		tmp.up=true
		players[dict["plid"]]["cards"]-=1
		update_pl_list()

func s_done(dict):
	pass

func s_status(dict):
	if dict["status"]=="ok": # and action!=""
		get_node("action").set_text("Ok")
		get_node("hand/refuse").set_disabled(true)
		action=""
		if lcardid!=-1:
			var chld = get_node("hand/cards").get_child(lcardid)
			get_node("hand/cards").remove_child(chld)
			chld.queue_free()
	elif dict["status"]=="bad":
		get_node("action").set_text("bad")
	rearrange()

func s_thrown(dict):
	action="T"
	if !dict["first"]:
		get_node("hand/refuse").set_disabled(false)
		get_node("hand/refuse").set_text("Refuse")
	get_node("action").set_text("Trown")

func s_answer(dict):
	action="A"
	get_node("hand/refuse").set_disabled(false)
	get_node("hand/refuse").set_text("Give up")
	get_node("action").set_text("Answer")

func s_gameinfo(dict):
	var hand = get_node("hand/cards")
	var offset = 600/(dict["hand"].size()+1)
	if offset > 80:
		offset=80
	for a in hand.get_children():
		hand.remove_child(a)
		a.queue_free()
	get_node("Deck/trump").face = dict["trumpcard"][0]
	get_node("Deck/trump").suit = dict["trumpcard"][1]
	get_node("Deck/trump").up=true
	players=dict["players"]
	#update_pl_list(dict["players"])
	#for a in dict["hand"]:
	for i in range(0,dict["hand"].size()):
		var tmp=card.instance()
		hand.add_child(tmp)
		tmp.set_pos(Vector2(offset*(i+1),0))
		tmp.id = i
		tmp.face = dict["hand"][i][0]
		tmp.suit = dict["hand"][i][1]
		tmp.up = true
		tmp.movable=true
	var dsize = dict["deck"]
	get_node("Deck/size").set_text(str(dsize))
	draw_deck(dsize)

func s_order(dict):
	update_pl_list(dict["lapl"],dict["vpl"])

func a_answer(cardid):
	var answ={};
	answ["card"]=cardid
	answ["signal"]="answer"
	print(answ.to_json())
	server.put_data(answ.to_json().to_utf8())
	lcardid=cardid

func a_thrown(cardid):
	var answ={};
	answ["card"]=cardid
	answ["signal"]="thrown"
	print(answ.to_json())
	server.put_data(answ.to_json().to_utf8())
	lcardid=cardid

func update_pl_list(lapl=gl_lapl, vpl=gl_vpl):
	pllist.set_text("")
	for i in range(0,players.size()):
		if i==lapl:
			pllist.insert_text_at_cursor("[A]")
		elif i==vpl:
			pllist.insert_text_at_cursor("[V]")
		pllist.insert_text_at_cursor(players[i]["name"] + ", " + str(players[i]["cards"]) + "\n")
	gl_lapl=lapl
	gl_vpl=vpl

func separate_jsons(json):
	var x = json.split("}{",false)
	for i in range(0,x.size()):
		if i!=0:
			x[i]=x[i].insert(0,"{")
		if i!=(x.size()-1):
			x[i]=x[i].insert(x[i].length(),"}")
	return x


func _on_refuse_pressed():
	if action=="T":
		a_thrown(-1)
	elif action=="A":
		a_answer(-1)

func rearrange():
	var hand = get_node("hand/cards")
	var size=hand.get_child_count();
	var offset=600/(size+1)
	if offset > 80:
		offset=80
	for i in range(0,size):
		var tmp = hand.get_child(i)
		tmp.set_pos(Vector2(offset*(i+1),0))
		tmp.id=i
