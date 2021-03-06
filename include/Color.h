//
// Copyright 2016 riteme
//

#ifndef RSRL_COLOR_H_
#define RSRL_COLOR_H_

namespace rsr {

struct Color4f {
    Color4f();
    Color4f(const float _red, const float _green, const float _blue);
    Color4f(const float _red, const float _green, const float _blue,
            const float _alpha);

    float red;
    float green;
    float blue;
    float alpha;

    /**
     * Blend b to this by alpha
     */
    Color4f operator+(const Color4f &b) const;

    /**
     * Scale color
     */
    Color4f operator*(const float r) const;

    /**
     * Negative color
     */
    Color4f operator-() const;

    Color4f &operator+=(const Color4f &b);
    Color4f &operator*=(const float r);

    /**
     * Correct color
     * If red, green, blue or alpha not in [0.0, 1.0], it will be cut to the
     * nearest bound
     */
    void correct();
};  // struct Color4f

}  // namespace rsr

#endif  // RSRL_COLOR_H_
