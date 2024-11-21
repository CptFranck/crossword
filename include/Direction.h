#ifndef DIRECTION_H
#define DIRECTION_H
#pragma once

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

static Direction randomDirection()
{
    std::uniform_int_distribution<size_t> dis(0, ALL_DIRECTIONS.size() - 1);
    Direction randomDirection = ALL_DIRECTIONS[dis(gen)];
    return randomDirection;
}

#endif