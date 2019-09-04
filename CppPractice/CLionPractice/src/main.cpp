#include "pch.h"

#include "TypeTraits.h"
#include <boost/type_index.hpp>

class Test {
};

template<class T>
void type_name(T) {
  std::cout << "\n Short name: " << boost::typeindex::type_id<T>().raw_name();
  std::cout << "\n Readable name: " << boost::typeindex::type_id<T>().pretty_name();
}

class IntWrapper;
std::unordered_set<IntWrapper *> G_Destroyed;

class IntWrapper {
 public:
  explicit IntWrapper(const int x) : m_Value(x) {}
  IntWrapper() = default;
  ~IntWrapper() {
    std::cout << "Destroyed: " << this << std::endl;
    G_Destroyed.insert(this);
  }

  auto GetValue() {
    if (::G_Destroyed.find(this) != ::G_Destroyed.end()) {
      std::cerr << "GetValue() called against destroyed object!" << std::endl;
    }
    return this->m_Value;
  }

  void SetValue(const int x) {
    this->m_Value = x;
  }

 private:
  int m_Value = 0;
};

auto bar() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, 100);

  auto ptr = std::make_shared<IntWrapper>();
  // https://neosmart.net/blog/2018/modern-c-isnt-memory-safe/
  // https://floating.io/2017/07/lambda-shared_ptr-memory-leak/
  auto closure = [&](int x) {
    if (!ptr) {
      std::cerr << "Shared pointer is removed" << std::endl;
      return;
    }

    for (auto i = 1; i <= x; i++) {
      if (i == (dist(mt) % x) || i == (dist(mt) % 3)) {
        std::cout << "Picked a number" << std::endl;
        ptr->SetValue(i);
        break;
      }
    }

    auto target = ptr->GetValue();
    std::cout << "The pointless convolution returned " << target << std::endl;
  };

  if ((dist(mt) % 20) == 2) {
    return std::bind(closure, 12);
  }
  return std::bind(closure, 5);
}

int main() {
  const auto a = 0;
  const auto b = "test";
  const auto c = new Test();
  const auto d = std::make_shared<Test>();

  std::cout << is_shared_ptr_t(a) << std::endl;
  std::cout << is_shared_ptr_t(b) << std::endl;
  std::cout << is_shared_ptr_t(c) << std::endl;
  std::cout << is_shared_ptr_t(d) << std::endl;

  type_name(a);
  type_name(b);
  type_name(c);
  type_name(d);
  delete c;

  std::cout << std::endl << std::endl;

  auto foo = bar();
  foo();
}