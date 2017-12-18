package com.example;

public enum Level {
    VERBOSE(6), DEBUG(5), INFO(4), WARN(3), ERROR(2), FATAL(1), NONE(0);

    private int mValue;

  
    private Level(int value) {
        this.mValue = value;
    }

    public int getValue() {
        return mValue;
    }

}
