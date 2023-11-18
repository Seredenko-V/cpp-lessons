#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

/// ЛР03. Стек и очередь. Вариант 11. Задача 3
/// Стек – динамический; очередь – статическая

struct Task {
    uint16_t priority;
    uint16_t task_time;
    uint16_t duration_time;
};

ostream& operator<<(ostream& out, Task task) {
    out << "Priority task = "s << task.priority << "; Task time = "s << task.task_time
        << "; Duration time = "s << task.duration_time << ".\n";
    return out;
}

// Для удобства работы с несколькими СТАТИЧЕСКИМИ очередями
struct Queue {
    int capacity = 0;
    int current_pos = 0;
    int priority = 1;
    Task* data;

    // Добавить элемент в конец очереди. Возвращает индекс куда будет добавлена новая задача
    int PushBack(Task task) {
        assert(capacity > current_pos);
        data[current_pos++] = task;
        return current_pos;
    }

    // Удалить элемент из начала очереди. Возвращает индекс куда будет добавлена новая задача
    int PopFront() {
        if (current_pos == 0) {
            return current_pos;
        }
        --current_pos;
        for (int i = 0; i < current_pos; ++i) {
            data[i] = data[i + 1];
        }
        return current_pos;
    }

    // Вывести содержимое очереди
    void Print(ostream& out = cout) {
        for (int i = 0; i < current_pos; ++ i) {
            out << data[i];
        }
    }
};

// Определить в какую очередь положить задачу
void DefineQueueForTask(Task task, Queue& first, Queue& second, Queue& third) {
    if (task.priority == first.priority) {
        first.PushBack(task);
    } else if (task.priority == second.priority) {
        second.PushBack(task);
    } else {
        third.PushBack(task);
    }
}

struct Stack {
    Task* task_values = nullptr;
    Stack* prev = nullptr;
};


ostream& operator<<(ostream& out, Stack* stack) {
    if (stack == nullptr) {
        out << "Stack is empty.\n"s;
        return out;
    }
    while (stack->prev != nullptr) {
        out << *stack->task_values;
        stack = stack->prev;
    }
    out << *stack->task_values;
    return out;
}

void AddStackElem(Stack*& node, uint16_t priority, uint16_t task_time, uint16_t duration_time) {
    Task* task = new Task;
    task->priority = priority;
    task->task_time = task_time;
    task->duration_time = duration_time;

    Stack* new_elem = new Stack;
    new_elem->prev = nullptr;
    new_elem->task_values = task;
    if (node == nullptr) {
        node = new_elem;
    } else {
        new_elem->prev = node;
        node = new_elem;
    }
}

void PopStackElem(Stack*& node) {
    if (node == nullptr) {
        return;
    }
    if (node->prev == nullptr) {
        delete node;
        node = nullptr;
        return;
    }
    Stack* tmp = node;
    node = node->prev;
    delete tmp;
}

void ClearStack(Stack*& node) {
    while(node != nullptr) {
        PopStackElem(node);
    }
}

// =========================== НАЧАЛО ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================>

void TestDefineQueueForTask() {
    constexpr int kCapacity = 10;
    Task first_tasks[kCapacity];
    Queue first{kCapacity, 0, 1, first_tasks};

    Task second_tasks[kCapacity];
    Queue second{kCapacity, 0, 2, second_tasks};

    Task third_tasks[kCapacity];
    Queue third{kCapacity, 0, 3, third_tasks};

    constexpr int kNumTestTasks = 5;
    Task test_tasks[kNumTestTasks]{
        {2, 3, 6},
        {1, 2, 7},
        {3, 23, 4126},
        {3, 5, 1},
        {1, 2, 2}
    };
    for (int i = 0; i < kNumTestTasks; ++i) {
        DefineQueueForTask(test_tasks[i], first, second, third);
    }
    assert(first.current_pos == 2);
    assert(second.current_pos == 1);
    assert(third.current_pos == 2);
    cerr << "TestDefineQueueForTask has passed\n"s;
}

void TestPushPopStack() {
    Stack* stack = nullptr;
    AddStackElem(stack, 5, 4, 6);
    AddStackElem(stack, 45, 12, 9);
    AddStackElem(stack, 2, 213, 9);
    { // Вывод должен быть в обратном порядке добавлению
        ostringstream expected_out{
            "Priority task = 2; Task time = 213; Duration time = 9.\n"s
            "Priority task = 45; Task time = 12; Duration time = 9.\n"s
            "Priority task = 5; Task time = 4; Duration time = 6.\n"s
        };
        ostringstream out;
        out << stack;
        assert(out.str() == expected_out.str());
    }{ // удаляем последний добавленный элемент
        ostringstream expected_out{
            "Priority task = 45; Task time = 12; Duration time = 9.\n"s
            "Priority task = 5; Task time = 4; Duration time = 6.\n"s
        };
        ostringstream out;
        PopStackElem(stack);
        out << stack;
        assert(out.str() == expected_out.str());
    }{ // удаляем все остальные элементы
        ostringstream expected_out{
            "Stack is empty.\n"s
        };
        ostringstream out;
        PopStackElem(stack);
        PopStackElem(stack);
        out << stack;
        assert(out.str() == expected_out.str());
    }{ // удаление элементов из пустого стека
        ostringstream expected_out{
            "Stack is empty.\n"s
        };
        ostringstream out;
        for (int i = 0; i < 10; ++i) {
            PopStackElem(stack);
        }
        out << stack;
        assert(out.str() == expected_out.str());
    }
    cerr << "TestPushPopStack has passed\n"s;
}

void RunAllTests() {
    TestDefineQueueForTask();
    TestPushPopStack();
    cerr << ">>> AllTests has passed <<<\n"s;
    cerr << "===========================\n"s;
}

// <=========================== КОНЕЦ ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================


/*void processorLoop(TaskList *&IncomingTask) {
    TaskList *Stack = NULL;
    TaskList *Queue = NULL;
    Task *OurProcessor = new Task;
    OurProcessor->priority = 0;
    OurProcessor->duration_time = 0;
    bool emptyQueue = true; //Проверка пустоты Очереди
    bool emptyStack = true; //Проверка пустоты Стека
    bool processorIsFree = true; //Проверка занятости процессора
    bool allTasksGone = false;
    int timer = 1;
    while(true) {
        if (!allTasksGone) {
            if (IncomingTask->task_values->task_time == timer) {
                pushToQueue(IncomingTask, Queue, emptyQueue, allTasksGone);
            }
        }
        if (!emptyQueue) {
            if (Queue->task_values->priority > OurProcessor->priority || processorIsFree) {
                if (OurProcessor->duration_time > 0) {
                    pushToStack(Stack, OurProcessor, emptyStack, processorIsFree);
                }
                getFromQueue(Queue, OurProcessor, emptyQueue, processorIsFree);
                while (true){
                    if (!emptyQueue) {
                        if (Queue->task_values->priority > OurProcessor->priority) {
                            pushToStack(Stack, OurProcessor, emptyStack, processorIsFree);
                            getFromQueue(Queue, OurProcessor, emptyQueue, processorIsFree);
                        }
                        else
                        break;
                    }
                    else
                    break;
                }
            }
        } else if (!emptyStack) {
            if (processorIsFree)
            getFromStack(Stack, OurProcessor, emptyStack, processorIsFree);
        }
        cout << endl << “Идет “ << timer << “ такт” << endl;
        if (!allTasksGone) {
            cout << “Входные задания” << endl;
            showStruct(IncomingTask);
        }
        if (!emptyStack) {
            cout << “Содержимое стэка” << endl;
            showStruct(Stack);
        }
        if (!emptyQueue) {
            cout << “Содержимое очереди” << endl;
            showStruct(Queue);
        }
        if (!processorIsFree) {
            cout << “Содержимое процессора” << endl;
            showStructElem(OurProcessor);
        } else {
            cout << «Процессор свободен» << endl;
        }
        if (!processorIsFree) {
            if (OurProcessor->duration_time) {
                OurProcessor->duration_time--;
            }
            if(OurProcessor->duration_time<=0) {
                OurProcessor->duration_time = 0;
                OurProcessor->priority = 0;
                processorIsFree = true;
            }
        }
        timer++;
        if (emptyStack && emptyQueue && processorIsFree && allTasksGone)
        break;
    }
    IncomingTask=NULL;
} */

int main() {
    RunAllTests();
    return 0;
}
