extends Control

var anim=false
var movable

func _ready():
	pass

func _on_Control_mouse_enter():
	if get_parent().movable and get_tree().get_root().get_node("Node").action!="":
		anim=true
		set_pos(Vector2(0,-20))
		#get_tree().get_root().get_node("Node").cselected=true
		#get_parent().get_node("AnimationPlayer").play("up")


func _on_Control_mouse_exit():
	if get_parent().movable:
		set_pos(Vector2(0,0))
		anim=false
		#get_tree().get_root().get_node("Node").cselected=false
		#get_parent().get_node("AnimationPlayer").play("down")


func _on_Control_input_event( event ):
	if event.type == InputEvent.MOUSE_BUTTON and event.pressed and get_tree().get_root().get_node("Node").action!="":
		if get_tree().get_root().get_node("Node").action=="A":
			get_tree().get_root().get_node("Node").a_answer(get_parent().id)
			print("Apush\n")
		elif get_tree().get_root().get_node("Node").action=="T":
			get_tree().get_root().get_node("Node").a_thrown(get_parent().id)
			print("Tpush\n")

