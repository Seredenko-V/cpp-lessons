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
    int priority = 0;
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
    void Print(ostream& out = cout) const noexcept {
        if (IsEmpty()) {
            out << "Queue is empty.\n"s;
            return;
        }
        for (int i = 0; i < current_pos; ++ i) {
            out << data[i];
        }
    }

    // Пуста ли очередь
    bool IsEmpty() const noexcept {
        assert(current_pos >= 0);
        return !current_pos;
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

struct Processor {
    Task current_task;
    Queue& high; // высокий
    Queue& medium; // средний
    Queue& low; // низкий
    Stack*& stack;
    int timer = 1;

    bool AllQueueIsEmpty() const noexcept {
        return high.IsEmpty() && medium.IsEmpty() && low.IsEmpty();
    }

    bool IsEmpty() const noexcept {
        return current_task.duration_time == 0 && AllQueueIsEmpty() && stack == nullptr;
    }

    // Положить на стек текущую задачу если она не завершена и взять более приоритетную
    void AddCurrentTaskToStackAndTakeNewTask(Queue& queue) {
        if (current_task.duration_time != 0) {
            AddStackElem(stack, current_task.priority, current_task.task_time, current_task.duration_time);
        }
        current_task = queue.data[0];
        queue.PopFront();
    }

    void Step() {
        if (IsEmpty()) {
            return;
        }
        if (current_task.duration_time == 0) {
            // очередь с задачами высокого приоритета НЕ пуста и первая в очереди задача "не из будущего"
            if (!high.IsEmpty() && high.data[0].task_time <= timer) {
                AddCurrentTaskToStackAndTakeNewTask(high);
            } else if (!medium.IsEmpty() && medium.data[0].task_time <= timer) { // очередь с задачами среднего приоритета НЕ пуста
                AddCurrentTaskToStackAndTakeNewTask(medium);
            } else if (!low.IsEmpty() && medium.data[0].task_time <= timer) {
                AddCurrentTaskToStackAndTakeNewTask(low);
            } else {
                Task* task = stack->task_values;
                current_task = {task->priority, task->task_time, task->duration_time};
                PopStackElem(stack);
            }
        } else {
            if (current_task.priority == 1) { // средний приоритет
                // очередь с задачами высокого приоритета НЕ пуста и первая в очереди задача "не из будущего"
                if (!high.IsEmpty() && high.data[0].task_time <= timer) {
                    AddCurrentTaskToStackAndTakeNewTask(high);
                }
            } else if (current_task.priority == 2) { // низкий приоритет
                if (!high.IsEmpty() && high.data[0].task_time <= timer) { // очередь с задачами высокого приоритета НЕ пуста
                    AddCurrentTaskToStackAndTakeNewTask(high);
                } else if (!medium.IsEmpty() && medium.data[0].task_time <= timer) { // очередь с задачами среднего приоритета НЕ пуста
                    AddCurrentTaskToStackAndTakeNewTask(medium);
                }
            }
        }

        cout << ">Tact "s << timer << endl;
        cout << ">Current task: "s << current_task;
        cout << ">High priority queue:\n"s;
        high.Print();
        cout << ">Medium priority queue:\n"s;
        medium.Print();
        cout << ">Low priority queue:\n"s;
        low.Print();
        cout << ">Stack:\n"s << stack;
        cout << "==============================================================\n"s;
        ++timer;
        --current_task.duration_time;
    }
};

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

int main() {
    RunAllTests();
    constexpr int kCapacity = 5;

    Task high_data[kCapacity];
    Queue high{kCapacity, 0, 0, high_data}; // высокий
    high.PushBack({0, 2, 3});
    high.PushBack({0, 7, 2});

    Task medium_data[kCapacity];
    Queue medium{kCapacity, 0, 1, medium_data}; // средний
    medium.PushBack({1, 3, 5});

    Task low_data[kCapacity];
    Queue low{kCapacity, 0, 2, low_data}; // низкий
    low.PushBack({2, 4, 1});

    Stack* stack = nullptr;
    Processor proc{{0,1,1}, high, medium, low, stack};

    while (!proc.IsEmpty()) {
        proc.Step();
    }
    return 0;
}
