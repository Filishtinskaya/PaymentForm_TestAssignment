#include "ProductsList.h"

float ProductsList::totalPrice() {
    float res = 0;
    for (auto& product : data) {
        res += product.qty * product.price;
    }
    return res;
}
