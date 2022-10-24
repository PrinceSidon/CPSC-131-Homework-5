#include <iostream>
#include <vector>

template <class T>

//Class for a vector-based queue
class vect_queue {
  std::vector<T> vect_que;
  size_t size_;
  int que_front_;
  int que_back_;

  public:
    //Creates a queue with val as its only element
    vect_queue<T>(T val) {
      vect_que.push_back(val);
      size_ = 1;
      que_front_ = 0;
      que_back_ = 0;
    }

    //Returns the vector index of the value at the corresponding queue index
    int map(int i) {
      int j = 0;

      //Checks to make sure the vector isn't empty
      if (vect_que.size() != 0) {

        //Case where no jump is needed
        if (que_front_ + i < vect_que.size()) {
          j = i + que_front_;
        }

        //Case where jump is needed
        else {
          j = i + que_front_ - vect_que.size();
        }
      }
      return j;
    }

    //Returns the element at the front of the queue
    T front() const {
      return vect_que[que_front_];
    }

    //Returns the element at the front of the queue
    T back() const {
      return vect_que[que_back_];
    }

    //Removes the element at the front of the queue
    void deque() {
      
      //Case where the queue has more than one element
      if (size_ > 1) {
        size_--;
        vect_que[que_front_] = NULL;

        /*
        If the front of the queue is currently at the back of the
        vector, it is moved to the front of the vector
        */
        if (que_front_ == vect_que.size() - 1) {
          que_front_ = 0;
        }
          
        //Otherwise, the front of the queue is moved forward
        else {
          que_front_++;
        }
      }

      //Case where the queue has only one element
      else if (size_ == 1) {
        size_--;
        vect_que[que_front_] = NULL;

        //Since the queue is empty, the front and back are the same
        que_front_ = 0;
        que_back_ = 0;
      }

      //Otherwise it displays an error
      else {
        std::cout << "Error: Cannot deque in an empty queue" << "\n\n";
      }
      
    }

    //Adds val to the end of the queue
    void enque(T val) {
      
      //Case where the vector isn't full
      if (size_ < vect_que.size()) {
        
        //If the queue is empty, val is added to the front of the queue
        if (size_ == 0) {
          size_++;
          vect_que[que_front_] = val;
        }

        //Otherwise, val is added to the end of the queue
        else {
          size_++;
          if (que_back_ != vect_que.size() - 1) {
            vect_que[que_back_ + 1] = val;
            que_back_++;
          }
            
          /*
          If we are at the end of the vector, the back of the queue goes to
          the front of the vector
          */
          else { 
            vect_que[0] = val;
            que_back_ = 0;
          }
        }
      }

      //Case where the vector is full
      else if (size_ == vect_que.size()) {

        /*
        Creates a new vector with twice the size and fills in the
        original values and val
        */
        std::vector<T> new_vect_que;
        if (vect_que.size() > 0) {
          new_vect_que.resize(vect_que.size() * 2);
          for (int i = 0; i < size_; i++) {
            new_vect_que[que_front_ + i] = vect_que[map(i)];
          }

          new_vect_que[que_front_ + size_] = val;
          que_back_ = que_front_ + size_;

          //The original vector gets replaced by the new one
          vect_que = new_vect_que;
          size_++;
        }

        /*
        If the vector is empty beforehand, the size increases by 1 instead of
        doubling
        */
        else {
          new_vect_que.resize(1);
          new_vect_que.push_back(val);
          que_back_ = 1;
          vect_que = new_vect_que;
          size_++;
        }
      }

      //Otherwise it displays an error
      else {
        std::cout << "Error: size cannot exceed capacity" << "\n\n";
      }
    }

    //Prints out the full vector as well as the front and back indices
    void print_vect() const {
      for (int i = 0; i < vect_que.size(); i++) {
        std::cout << vect_que[i] << " ";
      }
      std::cout << "(Front: " << que_front_;
      std::cout << " Back: " << que_back_ << ")";
    }
};

int main() {
  //Case 1
  std::cout << "Case 1:" << "\n\n";

  vect_queue<int> test(1);
  test.deque();
  test.print_vect();
  
  std::cout << " -> ";

  test.enque(1);
  test.print_vect();
  std::cout << "\n\n\n";

  
  //Case 2
  std::cout << "Case 2:" << "\n\n";

  test.print_vect();
  
  std::cout << " -> ";

  test.enque(2);
  test.print_vect();
  std::cout << "\n\n\n";

  
  //Case 3
  std::cout << "Case 3:" << "\n\n";
  test.deque();
  test.print_vect();

  std::cout << " -> ";
  
  test.enque(3);
  test.print_vect();
  std::cout << "\n\n\n";

  
  //Case 4
  std::cout << "Case 4:" << "\n\n";

  test.deque();
  test.deque();
  test.enque(1);
  test.enque(2);
  test.print_vect();

  std::cout << " -> ";

  test.deque();
  test.print_vect();
  std::cout << "\n\n\n";


  //Case 5
  std::cout << "Case 5:" << "\n\n";

  test.enque(3);
  test.print_vect();
  
  std::cout << " -> ";

  test.deque();
  test.print_vect();
  std::cout << "\n\n\n";


  //Case 6
  std::cout << "Case 6:" << "\n\n";

  test.enque(4);
  test.deque();
  test.print_vect();

  std::cout << " -> ";

  test.deque();
  test.print_vect();
  std::cout << "\n\n\n";

  return 0;
}