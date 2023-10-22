#pragma once
class FrontMiddleBackQueue
{
public:
	FrontMiddleBackQueue();

	void pushFront(int value) {
        data_.push_front(value);
    }

	void pushMiddle(int value) {
        auto it = data_.begin();
        std::advance(it, data_.size() / 2);
        data_.insert(it, value);
    }

	void pushBack(int value) {
        data_.push_back(value);
    }

	int popFront() {
        if (data_.empty()) {
            return -1;
        }
        int front = data_.front();
        data_.pop_front();
        return front;
    }

	int popMiddle() {
        if (data_.empty()) {
            return -1;
        }
        auto it = data_.begin();
        std::advance(it, (data_.size() - 1) / 2);
        int middle = *it;
        data_.erase(it);
        return middle;
    }

	int popBack() {
        if (data_.empty()) {
            return -1;
        }
        int back = data_.back();
        data_.pop_back();
        return back;
    }
private:
    std::list<int> data_;
};

