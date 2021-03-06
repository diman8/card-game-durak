# Карточная игра "Дурак"
Игра-приложение писалась в качестве проекта на MeraSummerSchool 2016.
Целевая платформа исполнения - Linux.
Время разработки - менее 2х недель.

## Цели
* Напиcать реализацию сервера на C++ и клиента на GodotEngine

Фичи, которые хотелось внедрить, но не вышло:
* дополнительная функциональность:
	* игра нестандартными коллодами *(8 мастей, по 20 значений и т.д.)*
    * карта, меняющая козырь
    * мошенничество *(1 крапленная карта, 1 - лишняя)*
    * другие правила *(переводной, до кучи и т.д.)*
* прикручивание тач-интерфейса на клиенте

## План разработки
1. [X] Игра-приложение. Описание всей логики и классов в одном проекте.
2. [X] Разработка интерфейса общения клиент-сервер. (JSON)
3. [X] Переписывание приложения под сервер. Написание клиента на GodotEngine.
4. [ ] ~~Красивости и доп. функциональность.~~


## Ссылки
1. [Связывание epool и сокетов](https://banu.com/blog/2/how-to-use-epoll-a-complete-example-in-c/)
2. [JSON-библиотека для C++](https://github.com/nlohmann/json)
3. [Godot Engine](http://godotengine.org/)
4. [UTF-8 & UTF-16 in C++11](http://stackoverflow.com/questions/148403/utf8-to-from-wide-char-conversion-in-stl)
5. [Игральные карты разных лет](http://valhalla.ulver.com/f49/t22376.html)

## Screenshots
![Screenshot 1](https://raw.githubusercontent.com/diman8/card-game-durak/master/imgs/1.jpg)
![Screenshot 2](https://raw.githubusercontent.com/diman8/card-game-durak/master/imgs/2.jpg)
![Screenshot 3](https://raw.githubusercontent.com/diman8/card-game-durak/master/imgs/3.jpg)