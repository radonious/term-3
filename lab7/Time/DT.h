#pragma once

struct DT : public T {
    int year;
    int month;
    int day;

    bool operator ==(const DT& other) {
        if (year == other.year && month == other.month && day == other.day &&
            hour == other.hour && minute == other.minute && second == other.second && msecond == other.msecond)
        {
            return 1;
        } else {
            return 0;
        }
    }

    bool operator !=(const DT& other) {
        if (year != other.year || month != other.month || day != other.day ||
            hour != other.hour || minute != other.minute || second != other.second || msecond != other.msecond)
        {
            return 1;
        } else {
            return 0;
        }
    }

} typedef DT;