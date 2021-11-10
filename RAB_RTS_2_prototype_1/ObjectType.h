#pragma once

/*
Тип объекта на карте. используется для определения типа объекта по координатам во время выполнения
*/
enum class ObjectType {
	none,
	ground,
	unit,
	building,
	resource
};