#pragma once

#include <memory>
#include <mutex>

using namespace std;

namespace util
{
	class noncopyable
	{
	protected:
		noncopyable() = default;
		~noncopyable() = default;

		noncopyable(const noncopyable&) = delete;
		noncopyable& operator=(const noncopyable&) = delete;
	};

	template <typename T>
	class Singleton : public noncopyable
	{
	public:
		static shared_ptr<T> GetInstance();
		static void ReleaseInstance();

	private:
		template<class K>
		class singleton_wrapper : public K
		{
		public:
			~singleton_wrapper()
			{

			}
		};
		static std::mutex s_mutex;
		static shared_ptr<T> s_instance;
	};

	template <typename T>
	std::mutex Singleton<T>::s_mutex;

	template <typename T>
	shared_ptr<T> Singleton<T>::s_instance;

	template <typename T>
	shared_ptr<T> Singleton<T>::GetInstance()
	{
		if (!s_instance)
		{
			std::lock_guard<std::mutex> guard(s_mutex);
			if (!s_instance)
			{
				s_instance = make_shared<singleton_wrapper<T>>();
			}
		}

		return s_instance;
	}

	template <typename T>
	void Singleton<T>::ReleaseInstance()
	{
		if (s_instance)
		{
			std::lock_guard<std::mutex> guard(s_mutex);
			s_instance.reset();
		}
	}
}