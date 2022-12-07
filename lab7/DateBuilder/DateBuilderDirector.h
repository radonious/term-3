#pragma once

class DateBuilderDirector {
public:
    void constructBirthdayDate(DateBuilder* builder) {
        builder->reset();
        builder->setYear(2003);
        builder->setMonth(9);
        builder->setDay(10);
        builder->setHour(19);
    }
    void constructNSKFoundationDate(DateBuilder* builder) {
        builder->reset();
        builder->setYear(1893);
        builder->setMonth(4);
        builder->setDay(30);
    }
};
