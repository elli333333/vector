//
// Created by ellie on 9/7/23.
//

#ifndef VECTOR_ENTITY_HPP
#define VECTOR_ENTITY_HPP

#include "common.hpp"

enum tag {
    undefined,
    player,
    fixed,
    enemy,
    t_text
};

enum shape {
    s_text,
    point,
    line,
    tri,
    square,
    penta,
    hexa
};


class entity {
private:
protected:
    u16 max_hp, curr_hp;
    tag entity_tag = tag::undefined;
    shape entity_shape = shape::point;

    bool is_hostile = (entity_tag == tag::enemy);

    u32 entity_colour;

public:

};


#endif //VECTOR_ENTITY_HPP
