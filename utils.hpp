#pragma once

/*
 * This function maps a value from one range to another.
 * Parameters:
 * - `fr_lower`: Lower bound of the input range
 * - `fr_upper`: Upper bound of the input range
 * - `to_lower`: Lower bound of the output range
 * - `to_upper`: Upper bound of the output range
 * - `value`: The value to map
 * Returns:
 * - The mapped value or -1 if the input range is invalid
 */
int map_range_val_from(int fr_lower, int fr_upper, int to_lower, int to_upper, int value)
{
    if (fr_lower == fr_upper || to_lower == to_upper) {
        return -1;
    }
    float scale = static_cast<float>(to_upper - to_lower) / (fr_upper - fr_lower);
    return to_lower + static_cast<int>((value - fr_lower) * scale);
}
