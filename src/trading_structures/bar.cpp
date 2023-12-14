//
// Created by letit6E on 04.12.2023.
//

#include "bar.h"

std::istream &operator>>(std::istream &in, Bar &bar) {
    char sep;

    in >> bar.open >> sep
       >> bar.close >> sep
       >> bar.high >> sep
       >> bar.low >> sep
       >> bar.volume >> sep
       >> bar.size >> sep
       >> bar.signed_volume >> sep
       >> bar.signed_size >> sep
       >> bar.directed_volume >> sep
       >> bar.directed_size >> sep
       >> bar.vwap >> sep
       >> bar.startstamp >> sep
       >> bar.stopstamp >> sep
       >> bar.duration >> sep
       >> bar.length;

    bar.price_volume_sum = bar.vwap * bar.length;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Bar &bar) {
    char sep = ',';

    out << bar.open << sep
       << bar.close << sep
       << bar.high << sep
       << bar.low << sep
       << bar.volume << sep
       << bar.size << sep
       << bar.signed_volume << sep
       << bar.signed_size << sep
       << bar.directed_volume << sep
       << bar.directed_size << sep
       << bar.vwap << sep
       << bar.startstamp << sep
       << bar.stopstamp << sep
       << bar.duration << sep
       << bar.length;

    return out;
}
