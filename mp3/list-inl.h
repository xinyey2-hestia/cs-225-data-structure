/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode *temp =head_;
  ListNode *next =NULL;
  while (temp!=NULL){
    next = temp->next;
    delete  temp;
    temp = next;

    if (temp == this->tail_)
    {
    delete temp;
  head_ =NULL;
tail_ =NULL;
temp =NULL;
length_ = 0;
}
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  ListNode* front = new ListNode(ndata);


  if(length_==0){
    head_= front;
    tail_= front;

  }
  else{
  front->next = head_;
  head_->prev = front;
  head_ = front;
  front->prev  =NULL;

}

length_ = length_+1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1

  ListNode* back= new ListNode(ndata);
  if (length_==0){
    head_ = back;
    tail_ = back;


  }
  else{
  tail_->next = back;
  back->prev = tail_;
  tail_ = back;
  back->next=NULL;
}
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {

  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3

    if (startPoint==endPoint||startPoint==NULL||endPoint==NULL)
    return;
    ListNode *begin= startPoint;
    ListNode* end = endPoint;
    ListNode* beforebegin = startPoint->prev;
    ListNode* afterend = endPoint->next;


    while (startPoint!=endPoint){
      ListNode* tempprev = startPoint->prev;
      startPoint->prev= startPoint->next;
      startPoint->next = tempprev;
      startPoint = startPoint->prev;

    }
    startPoint->next = startPoint->prev;
    startPoint->prev =beforebegin;
    endPoint = begin;
    endPoint->next = afterend;


    if (beforebegin==NULL){
        head_ = startPoint;
      }
      else  beforebegin->next=startPoint ;

    if (afterend==NULL){
      tail_ = endPoint;
    }
    else afterend->prev = endPoint;


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
if (length_==0||n<=1) return;
  ListNode* begin = head_;
  ListNode* traverse = head_;
  for(int i=0;i<length_/n;i++){

    for (int j=0;j<n-1;j++){
      traverse= traverse->next;
    }

    reverse(begin,traverse);
    begin = traverse->next;
    traverse = traverse->next;
}


while (traverse!=NULL&&traverse!=tail_){
  traverse = traverse->next;
}
reverse (begin,traverse);



}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (length_==0||length_==1||length_==2) return;
  ListNode* cur = head_;
  ListNode* newend=tail_;
  ListNode* needmove =  NULL;

  while((cur->next)!=newend){
    needmove = cur->next;
    cur->next =cur->next->next;
    cur->next->prev = cur;
    newend->next = needmove;
    needmove->prev = newend;
    needmove->next =NULL;

    cur = cur->next;
    newend = newend->next;


  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    ListNode* newhead =  start;
    if (newhead == NULL) return start;
    for (int i=0; i<splitPoint;i++){
      newhead = newhead->next;
    }
    ListNode* temp = newhead->prev;
    newhead->prev = NULL;
    temp->next = NULL;
    return newhead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* temp1 = first;
  ListNode* temp2 = second;
  ListNode* start = NULL;
  ListNode* forever;
  if (first==NULL)return second;
  if (second==NULL) return first;
  if (first->data<second->data){
  start = first;
  temp1 = temp1->next;
  forever = first;
}
  else{
  start = second;
  temp2= temp2->next;
  forever =second;
}

while (temp1!=NULL&&temp2!=NULL){
  if(temp1->data<temp2->data){
    start->next = temp1;
    temp1->prev = start;
    temp1 = temp1->next;
  }
  else{
    start->next = temp2;
    temp2->prev = start;
    temp2 = temp2->next;
  }
  start = start->next;
}

if (temp1!=NULL){
  start->next = temp1;
}
if (temp2!=NULL){
  start->next = temp2;
}

  return forever;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength==1) return start;
    
    ListNode* half2 = split(start,chainLength/2);
    return merge(mergesort(start,chainLength/2),mergesort(half2, chainLength-chainLength/2));
}
