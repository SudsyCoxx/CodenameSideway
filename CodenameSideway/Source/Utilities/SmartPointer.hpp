#pragma once

namespace Utilities {
	template < typename T >
	class SmartPointer {
		class RefCount {
		public:
			void AddRef() {
				m_count++;
			}

			int Release() {
				return --m_count;
			}

		private:
			int m_count;

		protected:
		};

	public:
		SmartPointer()
			: m_data(0), m_refCount(0)
		{
			m_refCount = new RefCount();
			m_refCount->AddRef();
		}

		SmartPointer(T* pValue)
			: m_data(pValue), m_refCount(0)
		{
			m_refCount = new RefCount();
			m_refCount->AddRef();
		}

		SmartPointer(const SmartPointer<T>& sp)
			: m_data(sp.m_data), m_refCount(sp.m_refCount)
		{
			m_refCount->AddRef();
		}

		~SmartPointer() {
			if (m_refCount->Release() == 0) {
				delete m_data;
				delete m_refCount;
			}
		}

		T& operator* () { return *m_data; }
		T* operator-> () { return m_data; }

		SmartPointer<T>& operator = (const SmartPointer<T>& sp) {
			if (this != &sp) {
				if (m_refCount->Release() == 0) {
					delete m_data;
					delete m_refCount;
				}

				m_data = sp.m_data;
				m_refCount = sp.reference;
				m_refCount->AddRef();
			}
			return *this;
		}

	private:
		T*    m_data;
		RefCount* m_refCount;
	
	protected:
	};
}