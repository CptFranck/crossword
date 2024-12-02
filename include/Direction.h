#ifndef DIRECTION_H
#define DIRECTION_H
#pragma once

#include <random>
#include <vector>

enum Direction
{
    HORIZONTAL,
    VERTICAL
};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::vector<Direction> ALL_DIRECTIONS({Direction::HORIZONTAL,
                                              Direction::VERTICAL});

Direction randomDirection();

#endif