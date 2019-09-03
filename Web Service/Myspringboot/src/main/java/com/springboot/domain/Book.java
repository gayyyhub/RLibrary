package com.springboot.domain;


import java.io.Serializable;

public class Book implements Serializable {

    private String identity;
    private String name;
    private String shelf;
    private String row;
    private String col;

    @Override
    public String toString() {
        return "Book{" +
                "identity='" + identity + '\'' +
                ", name='" + name + '\'' +
                ", shelf='" + shelf + '\'' +
                ", row='" + row + '\'' +
                ", col='" + col + '\'' +
                '}';
    }

    public String getIdentity() {
        return identity;
    }

    public void setIdentity(String identity) {
        this.identity = identity;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getShelf() {
        return shelf;
    }

    public void setShelf(String shelf) {
        this.shelf = shelf;
    }

    public String getRow() {
        return row;
    }

    public void setRow(String row) {
        this.row = row;
    }

    public String getCol() {
        return col;
    }

    public void setCol(String col) {
        this.col = col;
    }
}
