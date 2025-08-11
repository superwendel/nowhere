typedef struct Vec2
{
	f32 x;
	f32 y;
} Vec2;

typedef struct IVec2
{
	i32 x;
	i32 y;
} IVec2;

typedef struct Vec4
{
	union
	{
		f32 values[4];
		struct
		{
			f32 x, y, z, w;
		};
		struct
		{
			f32 r, g, b, a;
		};
	};
} Vec4;

typedef struct Mat4
{
	union
	{
		Vec4 values[4]; // Access columns as Vec4
		f32 m[4][4];   // Access elements as m[col][row]
		struct
		{
			f32 ax, bx, cx, dx;
			f32 ay, by, cy, dy;
			f32 az, bz, cz, dz;
			f32 aw, bw, cw, dw;
		};
	};
} Mat4;

ZINLINE Vec2 vec2_div_scalar(Vec2 v, f32 scalar)
{
	return (Vec2){v.x / scalar, v.y / scalar};
}

ZINLINE Vec2 vec2_mul_scalar(Vec2 v, f32 scalar)
{
	return (Vec2){v.x * scalar, v.y * scalar};
}

ZINLINE Vec2 vec2_sub(Vec2 a, Vec2 b)
{
	return (Vec2){a.x - b.x, a.y - b.y};
}

ZINLINE bool vec2_is_nonzero(Vec2 v)
{
	return v.x != 0.0f && v.y != 0.0f;
}

ZINLINE IVec2 ivec2_sub(IVec2 a, IVec2 b)
{
	return (IVec2){a.x - b.x, a.y - b.y};
}

ZINLINE void ivec2_sub_assign_scalar(IVec2* v, i32 value)
{
	v->x -= value;
	v->y -= value;
}

ZINLINE void ivec2_add_assign_scalar(IVec2* v, i32 value)
{
	v->x += value;
	v->y += value;
}

ZINLINE IVec2 ivec2_div_scalar(IVec2 v, i32 scalar)
{
	return (IVec2){v.x / scalar, v.y / scalar};
}

ZINLINE bool vec4_equals(Vec4 a, Vec4 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

ZINLINE i32 sign_i32(i32 x)
{
	return (x >= 0) ? 1 : -1;
}

ZINLINE f32 sign_f32(f32 x)
{
	return (x >= 0.0f) ? 1.0f : -1.0f;
}

ZINLINE i32 min_i32(i32 a, i32 b)
{
	return (a < b) ? a : b;
}

ZINLINE i32 max_i32(i32 a, i32 b)
{
	return (a > b) ? a : b;
}

ZINLINE i64 max_i64(i64 a, i64 b)
{
	return (a > b) ? a : b;
}

ZINLINE f32 max_f32(f32 a, f32 b)
{
	return (a > b) ? a : b;
}

ZINLINE f32 min_f32(f32 a, f32 b)
{
	return (a < b) ? a : b;
}

ZINLINE f32 approach_f32(f32 current, f32 target, f32 increase)
{
	if (current < target)
	{
		return min_f32(current + increase, target);
	}
	return max_f32(current - increase, target);
}

ZINLINE f32 lerp_f32(f32 a, f32 b, f32 t)
{
	return a + (b - a) * t;
}

ZINLINE Vec2 ivec2_to_vec2(IVec2 v)
{
	return (Vec2){(f32)v.x, (f32)v.y};
}

ZINLINE Vec2 lerp_vec2(Vec2 a, Vec2 b, f32 t)
{
	Vec2 result;
	result.x = lerp_f32(a.x, b.x, t);
	result.y = lerp_f32(a.y, b.y, t);
	return result;
}

ZINLINE IVec2 lerp_ivec2(IVec2 a, IVec2 b, f32 t)
{
	IVec2 result;
	result.x = (i32)floorf(lerp_f32((f32)a.x, (f32)b.x, t));
	result.y = (i32)floorf(lerp_f32((f32)a.y, (f32)b.y, t));
	return result;
}