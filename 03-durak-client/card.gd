tool
extends Node

export(int, 0, 12) var face=0 setget set_face
export(int, 0, 3) var suit=0 setget set_suit
export(bool) var up=false setget set_up
export(bool) var movable=false
export(int) var id
var fuckingbool=false

func set_up(a):
	up=a
	accept()

func set_face(a):
	face=a
	accept()

func set_suit(a):
	suit=a
	accept()


func accept():	
	if (fuckingbool && up):
		var a = fposmod((face+1),13)
		get_node("Control/CardSprite").set_frame(a+13*suit)
	elif(fuckingbool):
		get_node("Control/CardSprite").set_frame(52)

func _on_CardSprite_enter_tree():
	fuckingbool=true
	accept()