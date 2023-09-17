//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_FORCE_H
#define CLIB_FORCE_H


namespace swerve{
    struct Force {
        double fx;
        double fy;

        Force operator+(const Force &other); 
        double operator*(const Force &other);
        Force operator*(double scalar);
    };

}
#endif //CLIB_FORCE_H
