//
// Created by letit6E on 04.12.2023.
//

#include "bar.h"

std::istream& operator>>(std::istream& in, Bar& bar) {
    char comma;

    in >> bar.startstamp >> comma
       >> bar.stopstamp >> comma
       >> bar.duration >> comma
       >> bar.length >> comma
       >> bar.open >> comma
       >> bar.close >> comma
       >> bar.high >> comma
       >> bar.low >> comma
       >> bar.volume >> comma
       >> bar.size >> comma
       >> bar.signed_volume >> comma
       >> bar.signed_size;


    double price_volume_total = bar.open * bar.volume;
    bar.vwap = price_volume_total / bar.size;

    return in;
}

std::ostream& operator<<(std::ostream& out, const Bar& bar) {
    out << bar.startstamp << ","
        << bar.stopstamp << ","
        << bar.duration << ","
        << bar.length << ","
        << bar.open << ","
        << bar.close << ","
        << bar.high << ","
        << bar.low << ","
        << bar.volume << ","
        << bar.size << ","
        << bar.signed_volume << ","
        << bar.signed_size << std::endl;

    return out;
}
