
#define QUEUE_SIZE_MAX_MESSAGES 20
#define QUEUE_SIZE_MAX_MESSAGE_SIZE 300

// define byte data type
typedef unsigned char byte;

class LoRaQueue
{
public:
    // status enum for the queue
    enum Status
    {
        OK,                         // the message was added to the queue successfully
        OK_OVERWRITE,               // the message was added to the queue, but it overwrote the oldest message in the queue because the queue was full
        FAILED_MSG_TOO_LARGE,       // the message was not added to the queue because it is larger than the maximum message size (QUEUE_SIZE_MAX_MESSAGE_SIZE)
        QUEUE_EMPTY                 // the queue is empty after this action
    };

    // add a message to the queue
    Status enqueue(const byte* data, int length)
    {
        Status status = Status::OK;
        if (length > QUEUE_SIZE_MAX_MESSAGE_SIZE)
        {
            return Status::FAILED_MSG_TOO_LARGE;
        }

        if (currentSize == QUEUE_SIZE_MAX_MESSAGES)
        {
            overwriteCount++;
            status = Status::OK_OVERWRITE;
        }
        else { currentSize++; }

        head = (head + 1) % QUEUE_SIZE_MAX_MESSAGES; // move head to the next position
        if (tail == head)
            tail = (tail + 1) % QUEUE_SIZE_MAX_MESSAGES; // move tail to the next position if the queue is full
        memcpy(buffer[head].data, data, length); // copy the data to the buffer
        buffer[head].length = length; // set the length of the message
        return status;
    }

    // remove a message from the queue
    Status dequeue(byte* data, int& length)
    {
        if (currentSize == 0)
        {
            length = 0;
            return Status::QUEUE_EMPTY;
        }
        memcpy(data, buffer[tail].data, buffer[tail].length); // copy the data from the buffer
        length = buffer[tail].length; // set the length of the message
        tail = (tail + 1) % QUEUE_SIZE_MAX_MESSAGES; // move tail to the next position
        currentSize--; // decrease the current size of the queue
        if (currentSize == 0)
        {
            return Status::QUEUE_EMPTY;
        }
        return Status::OK;
    }

    // percentage of the queue that is currently filled
    float getFillPercentage() const
    {
        return (currentSize / (float)QUEUE_SIZE_MAX_MESSAGES) * 100.0f;
    }

    // get total used capacity of the queue in bytes
    int getUsedCapacity() const
    {
        int usedCapacity = 0;
        for (int i = 0; i < currentSize; i++)
        {
            int index = (tail + i) % QUEUE_SIZE_MAX_MESSAGES;
            usedCapacity += buffer[index].length;
        }
        return usedCapacity;
    }

    // get the number of times a new message has overwritten the oldest message in the queue
    unsigned long getOverwriteCount() const
    {
        return overwriteCount;
    }

    // clear the queue
    void resetQueue()
    {
        head = 0;
        tail = 0;
        currentSize = 0;
        overwriteCount = 0;
    }

private:
    // 2d buffer for storing the data to be sent
    struct Message
    {
        byte data[QUEUE_SIZE_MAX_MESSAGE_SIZE];
        int length;
    };
    Message buffer[QUEUE_SIZE_MAX_MESSAGES];
    int head = 0; // index of the first element in the queue
    int tail = 0; // index of the last element in the queue
    int currentSize = 0; // current number of messages in the queue
    unsigned long overwriteCount = 0; // count of how many times a new message has overwritten the oldest message in the queue
};