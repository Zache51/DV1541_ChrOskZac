#version 430
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 colorG;
out vec3 worldPosG;
out vec3 vn;

void main () {
	colorG = vec3 (0.7, 0.1, 0.8f);
	
	//worldPosG = (model * vec4(vertex_position, 1.0)).xyz;
	//gl_Position = projection * view * model * vec4 (vertex_position, 1.0);
	gl_Position = vec4 (vertex_position, 1.0);
	worldPosG = vertex_position;
	
	vn = vertex_normal;
}