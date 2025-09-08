struct vec2
{
	f32 x;
	f32 y;

	vec2 operator/(f32 scalar)
	{
		return {x / scalar, y / scalar};
	}

	vec2 operator*(f32 scalar)
	{
		return {x * scalar, y * scalar};
	}

	vec2 operator-(vec2 other)
	{
		return {x - other.x, y - other.y};
	}

	operator bool()
	{
		return x != 0.0f && y != 0.0f;
	}
};

struct ivec2
{
	i32 x;
	i32 y;

	ivec2 operator-(ivec2 other)
	{
    	return {x - other.x, y - other.y};
	}

	ivec2& operator-=(i32 value)
	{
		x -= value; 
		y -= value;
    
		return *this;
	}
  
	ivec2& operator+=(i32 value)
	{
		x += value; 
		y += value;
    
		return *this;
	}

	ivec2 operator/(i32 scalar)
	{
		return {x / scalar, y / scalar};
	}
};

struct vec4
{
	union
	{
		f32 values[4];
		
		struct
		{
			f32 x;
			f32 y;
			f32 z;
			f32 w;
		};
    
		struct
		{
			f32 r;
			f32 g;
			f32 b;
			f32 a;
		};
	};

	f32& operator[](int idx)
	{
		return values[idx];
	}

	bool operator==(vec4 other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
};

struct mat4
{
	union 
	{
		vec4 values[4];
		struct
		{
			f32 ax;
			f32 bx;
			f32 cx;
			f32 dx;

			f32 ay;
			f32 by;
			f32 cy;
			f32 dy;

			f32 az;
			f32 bz;
			f32 cz;
			f32 dz;
     
			f32 aw;
			f32 bw;
			f32 cw;
			f32 dw;
		};
	};

	vec4& operator[](int col)
	{
		return values[col];
	}
};

ZINLINE i32 sign(i32 x)
{
	return(x >= 0)? 1 : -1;
}

ZINLINE f32 sign(f32 x)
{
	return (x >= 0.0f)? 1.0f : -1.0f;
}

ZINLINE i32 min(i32 a, i32 b)
{
	return (a < b)? a : b;
}

ZINLINE i32 max(i32 a, i32 b)
{
	return (a > b)? a : b;
}
	
ZINLINE i64 max(i64 a, i64 b)
{
	if(a > b)
	{
		return a;
	}

	return b;
}

ZINLINE f32 max(f32 a, f32 b)
{
	if(a > b)
	{
		return a;
	}

	return b;
}

ZINLINE f32 min(f32 a, f32 b)
{
	if(a < b)
	{
		return a;
	}
  
	return b;
}

f32 approach(f32 current, f32 target, f32 increase)
{
	if(current < target)
	{
		return min(current + increase, target);
	}
  
	return max(current - increase, target);
}

ZINLINE f32 lerp(f32 a, f32 b, f32 t)
{
	return a + (b - a) * t;
}

vec2 vec_2(ivec2 v)
{
	return vec2{(f32)v.x, (f32)v.y};
}

vec2 lerp(vec2 a, vec2 b, f32 t)
{
	vec2 result;
	result.x = lerp(a.x, b.x, t);
	result.y = lerp(a.y, b.y, t);
  
	return result;
}

ivec2 lerp(ivec2 a, ivec2 b, f32 t)
{
	ivec2 result;
	result.x = (i32)floorf(lerp((f32)a.x, (f32)b.x, t));
	result.y = (i32)floorf(lerp((f32)a.y, (f32)b.y, t));
	return result;
}