#pragma once

namespace Utilities {
	template <typename T>
	class Singleton {
		// USAGE: Need to declase Singleton a friend class so it can call constructor of base class
		// friend class Singleton<Type>;
	public:
		static T& GetInstance(){
			// Return a static instance of the class
			static T instance;
			return instance;
		}
	
	private:
		// USAGE : When using singleton, ensure the following 3 functions are marked delete or private at the very least
		// Type();
		// Type(const Type& s) = delete;
		// Type& operator=(const Type& s) = delete;

	protected:
	};
}