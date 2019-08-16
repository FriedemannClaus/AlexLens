#ifndef _MODE_H
#define _MODE_H

/**
 * Enumeration for all Modes in Program
 */
enum class Mode {
    /**
     * Optimal Mode uses only CPU
     */
            OPTIMAL,
    /**
     * High Perfomance uses all available heterogenous platforms
     */
            HIGH_PERFOMANCE,
    /**
     * Low Power uses only one Neural Compute Stick
     */
            LOW_POWER,
    /**
     * Energy Efficient uses all available Neural Compute Sticks
     */
            ENERGY_EFFICIENT};



#endif //_MODE_H