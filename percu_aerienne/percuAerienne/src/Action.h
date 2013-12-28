#pragma once
struct Action
{
    int instrument;
    int bird;
    float delta_x;
    float delta_y;
    float delta_z;
    float angle_x;
    float angle_y;
    float angle_z;
    float speed_x;
    float speed_y;
    float speed_z;
    float accel_x;
    float accel_y;
    float accel_z;
    float velo_city;

    enum class Type { RECORD, ENTER, BUMP, LEAVE};
    Type action;
};
