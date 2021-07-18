#include "mat.h"

const Mat4 identity(1);

/*
void log(const bool& thing)
{
    if(thing == true)
    {
        cout << "true";
    }
    else
    {
        cout << "false";
    }
    cout << endl;
}
*/

void log(const Rotation& thing)
{
    cout << "pitch=" << thing.pitch << " yaw=" << thing.yaw << " roll=" << thing.roll << endl;
}

void log(const Mat4& thing)
{
    cout << thing.a.x << " " << thing.b.x << " " << thing.c.x << " " << thing.d.x << endl;
    cout << thing.a.y << " " << thing.b.y << " " << thing.c.y << " " << thing.d.y << endl;
    cout << thing.a.z << " " << thing.b.z << " " << thing.c.z << " " << thing.d.z << endl;
    cout << thing.a.w << " " << thing.b.w << " " << thing.c.w << " " << thing.d.w << endl;
}

void log(const Mat3& thing)
{
    cout << thing.a.x << " " << thing.b.x << " " << thing.c.x << endl;
    cout << thing.a.y << " " << thing.b.y << " " << thing.c.y << endl;
    cout << thing.a.z << " " << thing.b.z << " " << thing.c.z << endl;
}

void log(const Vec1f& thing) {
    cout << thing.x << endl;
}

void log(const Vec2f& thing) {
    cout << thing.x << " " << thing.y << endl;
}

void log(const Vec3f& thing)
{
    cout << thing.x << " " << thing.y << " " << thing.z << endl;
}

void log(const Vec4f& thing)
{
    cout << thing.x << " " << thing.y << " " << thing.z << " " << thing.w << endl;
}

void log(const Vec1i& thing)
{
    cout << thing.x << endl;
}

void log(const Vec2i& thing)
{
    cout << thing.x << " " << thing.y << endl;
}

void log(const Vec3i& thing)
{
    cout << thing.x << " " << thing.y << " " << thing.z << endl;
}

void log(const Vec4i& thing)
{
    cout << thing.x << " " << thing.y << " " << thing.z << " " << thing.w << endl;
}


namespace mat{

    Vec2f::Vec2f(float x, float y) 
        : x(x), y(y) {}

    Vec3f::Vec3f(float x, float y, float z) 
        : x(x), y(y), z(z) {}

    Vec4f::Vec4f(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

    Vec1i::Vec1i(int x)
        : x(x) {}

    Vec2i::Vec2i(int x, int y)
        : x(x), y(y) {}

    Vec3i::Vec3i(int x, int y, int z)
        : x(x), y(y), z(z) {}

    Vec4i::Vec4i(int x, int y, int z, int w)
        : x(x), y(y), z(z), w(w) {}

    Mat4::Mat4(float n)
    {
        a.x = b.y = c.z = d.w = n;
    }

    Vec3f operator*(const Vec3f& thing, const float& scalar)
    {
        Vec3f result(thing.x * scalar, thing.y * scalar, thing.z * scalar);
        return result;
    }
    
    Vec3f operator*(const float& scalar, const Vec3f& thing)
    {
        return thing * scalar;
    }

    Mat4 translate(Mat4 a, const Vec3f& b)
    {
        a.d.x += b.x;
        a.d.y += b.y;
        a.d.z += b.z;
        return a;
    }

    Mat4 scale(Mat4 a, const Vec3f& b)
    {
        a.a.x *= b.x;
        a.b.y *= b.y;
        a.c.z *= b.z;
        return a;
    }

    Mat4 rotateX(Mat4 a, float theta)
    {
        a.a.x = 1;
        a.b.y = cos(theta);
        a.b.z = sin(theta);
        a.c.y = -sin(theta);
        a.c.z = cos(theta);
        a.d.w = 1;
        return a;
    }

    Mat4 rotateY(Mat4 a, float theta)
    {
        a.a.x = cos(theta);
        a.a.z = -sin(theta);
        a.b.y = 1;
        a.c.x = sin(theta);
        a.c.z = cos(theta);
        a.d.w = 1;
        return a;
    }

    Mat4 rotateZ(Mat4 a, float theta)
    {
        a.a.x = cos(theta);
        a.a.y = sin(theta);
        a.b.x = -sin(theta);
        a.b.y = cos(theta);
        a.c.z = 1;
        a.c.w = 1;
        return a;
    }

    Mat4 perspective(float close, float far, float fov, float R)
    {
        Mat4 p(0);
        float L = 2.0f * (float)tan(fov / 2) * close;

        float H = L / R;

        p.a.x = close * 2.0f / L;                   
        p.b.y = close * 2.0f / H;                   
        p.c.z = -(far + close) / (far - close);        
        p.d.z = 2.0f * far * close / (close - far); 

        p.c.w = -1;

        return p;
    }

    Vec4f multiply(const Mat4& a, const Vec4f& b)
    {
        //std::cout << "BBB";
        Vec4f rez;
        rez.x = a.a.x * b.x + a.b.x * b.y + a.c.x * b.z + a.d.x * b.w;
        rez.y = a.a.y * b.x + a.b.y * b.y + a.c.y * b.z + a.d.y * b.w;
        rez.z = a.a.z * b.x + a.b.z * b.y + a.c.z * b.z + a.d.z * b.w;
        rez.w = a.a.w * b.x + a.b.w * b.y + a.c.w * b.z + a.d.w * b.w;

        return rez;
    }

    Vec3f getDirectionFromRotation(const Rotation& rotation)
    {
        Vec3f direction;
        direction.x = -cos(rotation.pitch) * cos(rotation.yaw);
        direction.y = -sin(rotation.pitch);
        direction.z = -cos(rotation.pitch) * sin(rotation.yaw);
        direction = normalise(direction);

        return -direction;
    }

    float module(const Vec3f& a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    float module(const Vec2f& a)
    {
        return sqrt(a.x * a.x + a.y * a.y);
    }

    float dot(const Vec3f& a, const Vec3f& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    float dot(const Vec2f& a, const Vec2f& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    Vec3f projection(const Vec3f& a, const Vec3f& b)
    {
        float d = (module(b)) * (module(b)) / dot(a, b);
        Vec3f c;
        c.x = a.x * d;
        c.y = a.y * d;
        c.z = a.z * d;
        return c;
    }

    Vec3f normalise(Vec3f a)
    {
        float b = module(a);
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }

    Vec2f normalise(Vec2f a)
    {
        float b = module(a);
        a.x /= b;
        a.y /= b;
        return a;
    }

    Vec3f cross(const Vec3f& a, const Vec3f& b)
    {
        Vec3f rez;
        rez.x = a.y * b.z - a.z * b.y;
        rez.y = -(a.x * b.z - a.z * b.x);
        rez.z = a.x * b.y - a.y * b.x;
        return rez;
    }

    Vec3f multiplyScalar(Vec3f a, float b)
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }

    Vec3f multiplyScalar(Vec3f a, int b)
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }

    Vec3f add(const Vec3f& a, const Vec3f& b)
    {
        Vec3f c;
        c.x = a.x + b.x;
        c.y = a.y + b.y;
        c.z = a.z + b.z;
        return c;
    }

    Vec3f subtract(const Vec3f& a, const Vec3f& b)
    {
        Vec3f c;
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        c.z = a.z - b.z;
        return c;
    }

    Vec2f subtract(const Vec2f& a, const Vec2f& b)
    {
        Vec2f c;
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        return c;
    }

    int sgn(int n)
    {
        if (n > 0)
            return 1;
        else return -1;
    }

    int sgn(float n)
    {
        if (n > 0)
            return 1;
        else return -1;
    }

    float clampTwoSide(float minPossibleValue, float maxPossibleValue, float n)
    {
        if (n < minPossibleValue)
            return minPossibleValue;
        if (n > maxPossibleValue)
            return maxPossibleValue;
        return n;

    }

    float clampMin(float minPossibleValue, float n)
    {
        if (n < minPossibleValue)
            return minPossibleValue;
        else return n;
    }

    float clampMax(float maxPossibleValue, float n)
    {
        if (n > maxPossibleValue)
            return maxPossibleValue;
        else return n;
    }

};
