#pragma once

namespace Buffers {
	class VertexBufferObject {
	public:
		VertexBufferObject(unsigned int BufferType);
		~VertexBufferObject();

		void bind();
		void unbind();
		void bufferData(int Count, int SizeOfElement, void* Elements, unsigned int DrawType);
		
		inline const unsigned int GetID() { return m_buffer; }
	private:
		void genBuffer();

		unsigned int m_buffer;
		unsigned int m_type;

		bool m_enabled;

	protected:
	};
}

