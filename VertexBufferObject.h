#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
class VertexBufferObject {
private:
	unsigned int id;
	bool alreadyAttributed;
	std::vector<unsigned short> lengths;

public:
	VertexBufferObject() {
		glGenBuffers(1, &id);
		alreadyAttributed = false;
	}

	void add(short length) {
		lengths.push_back(length);
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
		if (!alreadyAttributed) {
			int sum = 0;
			for(auto length:lengths) sum+= length;
			int sumSoFar = 0;
			for (int i = 0; i < lengths.size(); i++) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, lengths[i], GL_FLOAT, GL_FALSE, sizeof(float) * sum, (void*)(sizeof(float)*sumSoFar));
				sumSoFar += lengths[i];
			}
			alreadyAttributed = true;
		}
	}

};