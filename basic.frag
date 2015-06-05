#version 330

in vec2 v_uv;
out vec4 FragColor;

uniform float u_Time;
uniform vec2 u_Resolution;

// Distance functions by Iñigo Quílez 
// http://iquilezles.org/www/articles/distfunctions/distfunctions.htm

// utility
mat4 makeRotation(float rads, float x, float y, float z)
{
    vec3 v = normalize(vec3(x, y, z));
    float c = cos(rads);
    float cp = 1. - c;
    float s = sin(rads);
    
    return mat4(c + cp * v.x * v.x,
                cp * v.x * v.y - v.z * s,
                cp * v.x * v.z + v.y * s,
                0.,
                
                cp * v.x * v.y + v.z * s,
                c + cp * v.y * v.y,
                cp * v.y * v.z - v.x * s,
                0.,
                
                cp * v.x * v.z - v.y * s,
                cp * v.y * v.z + v.x * s,
                c + cp * v.z * v.z,
                0.,
                
                0.0, 0.0, 0.0, 1.0);
}


// scene
#define MAX_STEPS 128
#define MAX_DEPTH 8.0

float sdBox( vec3 p, vec3 b )
{
	p = (makeRotation(u_Time, 1.0, 1.0, 1.0) * vec4(p, 1.0)).xyz;
	vec3 d = abs(p) - b;
	return min(max(d.x, max(d.y, d.z)), 0.0) + length(max(d, 0.0));
}

float repeatBox( vec3 p, vec3 c )
{
    vec3 q = -0.5 * c + mod(p,c);
    return sdBox(q, vec3(0.015 * (sin(u_Time) + 1.5)));
}

vec2 scene(in vec3 p)
{
	return vec2(repeatBox(p, vec3(0.15)), 1.0);
}

vec3 calcNormal(in vec3 p)
{
	vec3 e = vec3(0.001, 0.0, 0.0);
	
	vec3 n;
	
	n.x = scene(p + e.xyy).x - scene(p - e.xyy).x;
	n.y = scene(p + e.yxy).x - scene(p - e.yxy).x;
	n.z = scene(p + e.yyx).x - scene(p - e.yyx).x;
	
	return normalize(n);
}

vec2 intersect(in vec3 origin, in vec3 direction)
{
	float rayLength = 0.0;
    vec2 hit;
	for (int i = 0; i < MAX_STEPS; ++i)
	{
		if (rayLength > MAX_DEPTH)
			break;
		
		hit = scene(direction * rayLength + origin);
		if (hit.x < 0.001)
			break;
		
		// partially increment to reduce artifacts
		rayLength += 0.75 * hit.x;
	}
	
	return vec2(rayLength, hit.y);
}

void main()
{
	//setup space
	vec2 uv = v_uv;
	vec2 p = uv * 2.0 - 1.0; 
	p.x *= u_Resolution.x / u_Resolution.y;
	
	//setup camera
	vec3 camPosition = vec3(0.0, 0.0, 2.0);
	vec3 camUp = vec3(0.0, 1.0, 0.0);
	vec3 camDirection = vec3(0.0, 0.0, -1.0);
	vec3 camRight = cross(camDirection, camUp);
	vec3 rayDirection = normalize(p.x * camRight + 
								  p.y * camUp + 
								  1.5 * camDirection);
	
	vec3 color = vec3(0.0);
	vec2 result = intersect(camPosition, rayDirection);
	
	if (result.y > 0.5) // if we have a material
	{
		float constantAttenuation = 2.0;
		float linearAttenuation = 1.0;
		float quadraticAttenuation = 0.5;
		float dist = result.x;
		
		float att = 1.0 / (constantAttenuation + dist * (linearAttenuation  + quadraticAttenuation * dist));
			
		vec3 position = camPosition + rayDirection * result.x;
		vec3 normal = calcNormal(position);
		vec3 light = normalize(position + vec3(0., 0.8, -1. * (sin(u_Time) + 1.)));
		vec3 blight = vec3(-light.x, light.y, -light.z);
		vec3 R = reflect(rayDirection, normal);
		float specular = 0.5 * pow(clamp(dot(light, R), 0.0, 1.0), 8.0);
		
		if (result.y == 1.0)
		{
			color += vec3(0.75) * att;
			color += max(0., dot(normal, light)) * vec3(1.) * att;
			color += specular * att;
		}
	}

	FragColor = vec4(color, 1.0);
}