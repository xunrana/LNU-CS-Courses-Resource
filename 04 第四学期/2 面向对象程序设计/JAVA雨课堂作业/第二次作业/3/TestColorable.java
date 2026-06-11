package com.example.colorable;

public class TestColorable {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Square square = new Square(5.0, "red", true);
        System.out.println(square);
        System.out.println("Area: " + square.getArea());
        System.out.println("Perimeter: " + square.getPerimeter());
        square.howToColor();
	}
}
