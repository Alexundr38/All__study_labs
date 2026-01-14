void errors()
{
    cout << "error";
    exit(0);
}

class CustomStack {

    public:

        CustomStack(ListNode* Head = NULL)
        {
            mHead = Head;
        }

        ~CustomStack()
        {
            ListNode* temp;
            while (mHead != NULL)
            {
                temp = mHead;
                mHead = mHead->mNext;
                delete temp;
            }
        }

        void push(int val)
        {
            ListNode* new_el = new ListNode;
            new_el->mNext = mHead;
            new_el->mData = val;
            mHead = new_el;
        }

        void pop()
        {
            if (not empty())
            {
                ListNode* last_el = mHead;
                mHead = mHead->mNext;
                delete last_el;
            } 
            else
            {
                errors();
            } 
        }

        int top()
        {
            if (not empty())
            {
                return mHead->mData;
            }
            else
            {
                errors();
            }
        }

        size_t size()
        {
            size_t count = 0;
            ListNode* temp = mHead;
            while (temp != NULL)
            {
                count++;
                temp = temp->mNext;
            }
            return count;
        }

        bool empty()
        {
            if (mHead == NULL)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    // методы push, pop, size, empty, top + конструкторы, деструктор

    private:

    // поля класса, к которым не должно быть доступа извне
        void errors()
        {
            cout << "error";
            exit(0);
        }

    protected:  // в этом блоке должен быть указатель на голову

        ListNode* mHead;
};

void action(CustomStack* stack, char sign)
{
    int first, second;
    first = (*stack).top();
    (*stack).pop();
    second = (*stack).top();
    (*stack).pop();

    if (sign == '+')
    {
        int sum = first + second;
        (*stack).push(sum);
    }
    else if (sign == '-')
    {
        int diff = second - first;
        (*stack).push(diff);
    }
    else if (sign == '*')
    {
        int compos = first * second;
        (*stack).push(compos);
    }
    else if (sign == '/')
    {
        int part = second / first;
        (*stack).push(part);
    }
    else
    {
        errors();
    }
}

int main()
{
    char data[101];
    fgets(data, 100, stdin);

    int flag = 0;  
    CustomStack stack;

    for (size_t i = 0; i < strlen(data); i++)
    {
        if (data[i] == ' ' || data[i] == '\n')
        {
            int size = i - flag;
            int val;
            char value = '1';
            if (flag == -1) flag = 0;

            char* temp = new char[size+1]; 
            strncpy(temp, data + flag, size);

            if (size > 1)
            {
                val = stoi(temp);
            } 
            else if (isdigit(temp[0]))
            {
                val = stoi(temp);
            }
            else
            {
                value = temp[0];
            }

            if (value == '1')
            {
                stack.push(val);
                // znak
            }
            else
            {
                action(&stack, value);
                //chislo
            }

            flag = i + 1;
            delete temp;
        } 
    }

    int ans, len;
    ans = stack.top();
    len = stack.size();

    if (len != 1)
    {
        errors();
    }
    else
    {
        cout << ans;
    }
}
