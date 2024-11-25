#ifndef DIRECTION_H
#define DIRECTION_H
#pragma once

#include <random>
#include <vector>

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::vector<Direction> ALL_DIRECTIONS({Direction::UP,
                                              Direction::DOWN,
                                              Direction::RIGHT,
                                              Direction::LEFT});

Direction randomDirection();

#endif