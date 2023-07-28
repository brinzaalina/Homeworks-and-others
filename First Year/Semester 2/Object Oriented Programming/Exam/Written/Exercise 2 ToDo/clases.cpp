//
// Created by selen on 18/06/2021.
//

#include "clases.h"

Activity::Activity(const std::string &description, const std::string &time): description{description}, time{time} {

}

std::ostream &operator<<(std::ostream &ostream, const Activity &activity) {
    std::string result;
    result.append("Activity ");
    result.append(activity.description);
    result.append(" will take place at ");
    result.append(activity.time);
    ostream << result;
    return ostream;
}

bool Activity::operator<(const Activity &activity) const {
    return this->time < activity.time;
}
