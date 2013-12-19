#ifndef VECTOR_3_H_2013_12_19
#define VECTOR_3_H_2013_12_19

class Vector3
{
public:
  static constexpr float TO_RADIANS = (1.0f/180.f)*M_PI;
  static constexpr float TO_DEGREE  = 180.0f/M_PI;
  float x, y, z;
  	
  Vector3()
    :x(0), y(0), z(0)
  {		
  }
	
  Vector3(float _x, float _y, float _z)
    :x(_x), y(_y), z(_z)
  {
  }
	
  Vector3(const Vector3 &other)
  {
    this->x = other.x;
    this->y = other.y;
  }
	
  Vector3& set(const float &x, const float &y, const float &z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
  }
	
  Vector3& set(const Vector3 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
  }
	
  Vector3& add(const float &x,const float &y, const float &z)
  {
    this->x += x;
    this->y += y;
    this->z += z;
    return *this;
  }
	
  Vector3& add(const Vector3 &other)
  {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;    
    return *this;
  }
	
  Vector3& sub(const float &x,const float &y, const float &z)
  {
    this->x -= x;
    this->y -= y;
    this->z -= z;
    return *this;
  }
	
  Vector3& sub(const Vector3 &other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }
	
  Vector3& mul(const float &scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }
	
  float length() const
  {
    return sqrt(x*x + y*y + z*z);
  }
	
  Vector3& normalize(){
    float len = length();

    if(len != 0){
      x /= len;
      y /= len;
      z /= len;
    }
    return *this;
  }

  Vector3 normalizedVector() const {
    float len = length();
    float _x=0, _y=0, _z=0;
    if(len != 0){
      _x = x/len;
      _y = y/len;
      _z = z/len;
    }
    return Vector3(x,y,z);
  }
	
  float dist(Vector3 other){
    float distX = this->x - other.x;
    float distY = this->y - other.y;
    float distZ = this->z - other.z;
		
    return sqrt(distX*distX + distY*distY + distZ*distZ); 
  }
	
  float dist(float x, float y, float z){
    float distX = this->x - x;
    float distY = this->y - y;
    float distZ = this->z - z;
    return sqrt(distX*distX + distY*distY + distZ*distZ); 
  }

  //2乗距離
  float distSquared(Vector3 other){
    float distX = this->x - other.x;
    float distY = this->y - other.y;
    float distZ = this->z - other.z;
    
    return distX*distX + distY*distY + distZ*distZ; 
  }
	
  float distSquared(float x, float y){
    float distX = this->x - x;
    float distY = this->y - y;
    float distZ = this->z - z;
    
    return distX*distX + distY*distY + distZ*distZ; 
  }

  //内積
  float dot(const Vector3 &other)
  {
    return this->x*other.x + this->y*other.y + this->z*other.z;
  }

  //外積
  Vector3 cross(const Vector3 &other)
  {
    return Vector3(this->y*other.z - this->z*other.y,
                   this->z*other.x - this->x*other.z,
                   this->x*other*y - this->y*other.x);
  }

  float angleTo(const Vector3 &other)
  {
    float dot = this->x*other.x + this->y*other.y + this->z*other.z;
    float len1 = this->length();
    float len2 = other.length();

    //零ベクトルとの角度は0とする
    if(len1 ==0 || len2 == 0)
      return 0;
    
    return dot/len1/len2;
  }

  float distanceTo(const Vector3 &other)
  {
    float _x = other.x - this->x;
    float _y = other.y - this->y;
    float _z = other.z - this->z;
    return sqrt(_x*_x + _y*_y + _z*_z);
  }

  Vector3& operator=(const Vector3 &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;    
    return *this;
  }

  Vector3& operator-=(const Vector3 &other)
  {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }

  Vector3& operator+=(const Vector3 &other)
  {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  Vector3& operator*=(const float &scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  Vector3 operator+()
  {
    return *this;
  }

  Vector3 operator-()
  {
    return Vector3(-x, -y, -z);
  }

  Vector3 operator+(const Vector3 &rhs)
  {
    return Vector3(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z);
  }

  Vector3 operator-(const Vector3 &rhs)
  {
    return Vector3(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z);
  }

  Vector3 operator*(const float &k)
  {
    return Vector3(this->x*k, this->y*k, this->z*k);
  }

  friend Vector3 operator*(const float &k, const Vector3 &rhs)
  {
    return Vector3(this->x*k, this->y*k, this->z*k);
  }

  Vector3 operator/(const float &k)
  {
    return Vector3(this->x/k, this->y/k, this->z/k);
  }

  friend ostream& operator<<(const ostream &s, const Vector3 &rhs)
  {
    return s << "(" << this->x << "," << this->y << "," << this->z << ")" << endl;
  }
};
3
#endif
