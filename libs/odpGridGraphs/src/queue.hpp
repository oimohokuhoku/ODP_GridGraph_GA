#pragma once

namespace Collections{
	/// @brief エラーチェックいれていないので多分std::queueより速い. 計測はまだしてない
	template<class T>
	class Queue {
	public:
		Queue(int capacity);
		~Queue();
		void enqueue(const T& value);
		T dequeue();
		void clear();
		int count() const;
		bool empty() const;
		bool contain(const T& value) const;

	private:
		int _head;
		int _tail;
		T* _values;
		int _maxSize;

		Queue() = delete;
	};
}

template<class T>
Collections::Queue<T>::Queue(int capacity) {
	_values = new T[capacity];
	_maxSize = capacity;
	_head = 0;
	_tail = 0;
}

template<class T>
Collections::Queue<T>::~Queue() {
	delete[] _values;
}

/// @brief エンキュー(末尾に値を追加)
template<class T>
void Collections::Queue<T>::enqueue(const T& value) {
	_values[_tail] = value;
	_tail = (_tail + 1) % _maxSize;
}

/// @brief デキュー(先頭の値を取得して削除)
template<class T>
T Collections::Queue<T>::dequeue() {
	int temp = _values[_head];
	_head = (_head + 1) % _maxSize;
	return temp;
}

/// @brief 保持している要素数を取得
template<class T>
int Collections::Queue<T>::count() const {
	if (_head <= _tail) return _tail - _head;
	else return _maxSize - (_head - _tail);
}

/// @brief キューが要素を一つも持たないならtrueを返す
template<class T>
bool Collections::Queue<T>::empty() const {
	return (_head == _tail);
}

/// @brief 値を持っているか判定
template<class T>
bool Collections::Queue<T>::contain(const T& element) const {
	for (int i = _head; i < _tail; ++i) {
		if (_values[i] == element) return true;
	}
	return false;
}

/// @brief すべての要素を削除
template<class T>
void Collections::Queue<T>::clear() {
	_head = 0;
	_tail = 0;
}
