# Занятия по С++

Этот репозиторий посвящен занятиям по С++.
Для каждого студента создается отдельная ветка, в которой мы будем разбирать примеры и выполнять задания.  

* Задания появляются после каждого урока. 
* Выполненное задание оформляется как pull request в соответствующую ветку.

Настоящая инструкция для взаимодействия с локальным и удаленным репозиториями написана на основе **бесплатного** 
[курса по Git](https://practicum.yandex.ru/profile/git-basics/) от Яндекс Практикума. 
Поэтому если возникнет желание изучить основы Git, или возникнут дополнительные вопросы, рекомендую изучить этот курс.

## 1 Настройка окружения (Windows)
Если вы пользуетесь UNIX системой, то этот пункт вам не нужно изучать. Вам будет достаточно установить git через встроенный терминал.

На пером этапе следует установить консоль git bash для Windows. Скачать её установочник можно по [этой ссылке](https://git-scm.com/download/win). 
На странице скачивания, в разделе `Standalone Installer`, следует выбрать версию, которая соответствует архитектуре вашей системы.  

Рекомендуется чтобы путь к каталогу, в которой будет установлен git, не содержал пробелов и киррилицы. Другими словами, каталог, путь к которому 
выглядит примерно так

```
С:\Занятия по С++\My programs\Git
```

не является удачным решением. Лучше создать отдельную директорию для подобных программ разработки, например,

```
C:\dev
```


![path-install](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/path-install.png)


Остальные параметры во время установки менять не нужно, просто прожимаем "Далее" пока не установим.   

Если всё установилось успешно, то можно открыть git bash и написать там `git --version`.

![installed-git-bash](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/ready-git-bash.png)


## 2 Создание SSH ключа для взаимодействия с GitHub
1. Открываем git bash в произвольном месте
2. Переходим в домашнюю директорию

```
cd ~
```

3. Находясь в домашней директории (значок тильда `~`), вводим

```
ssh-keygen -t ed25519 -C "твоя почта на GitHub"
```

4. Когда вылетит это сообщение

```
Enter a file in which to save the key (C:\Users\<имя_пользователя>\.ssh\):
```
просто нажимаем Enter, никаких путей указывать не нужно.

5. Когда спросит кодовую фразу, лучше просто пропустить её ввод, чтобы не вводить её при каждом `git push`, т.е.

```
Enter passphrase (empty for no passphrase): [просто нажимаем enter] 
Enter same passphrase again: [просто нажимаем enter]
```

6. Проверяем наличие ключа

```
ls -a ~/.ssh
```
![created-ssh-key](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/created-ssh-key.png)

## 3 Привязываем SSH ключ к аккаунту на GitHub

1. Переходим в раздел "**Settings**"

![bind-ssh-1](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/bind-ssh-1.png)

2. Переходим в раздел "**SSH and GPG keys**"
![bind-ssh-2](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/bind-ssh-2.png)

3. Нажимаем на "**New SSH key**"

4. В открывшемся окне, в графе "Title" вводим название нашего ключа, например, "MyPC key". В графе "Key" - содержимое файла `~/.ssh/id_ed25519.pub`.
![bind-ssh-3](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/bind-ssh-3.png)

5. Проверяем правильность выполненных действий при помощи команды `ssh -T git@github.com`.  
Если появится надпись

```
The authenticity of host 'github.com (140.82.121.4)' can't be established. ED25519 key fingerprint is SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU. This key is not known by any other names. Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

то всё в порядке, просто нужно ввести `yes`, после чего появится это сообщение

```
Hi %ТВОЙ_АККАУНТ GITHUB%! You've successfully authenticated, but GitHub does not provide shell access.
```
![bind-ssh-4](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/bind-ssh-4.png)

6. Указываем свою почту в консоли git bash при помощи команды

```
git config --global user.email "you@example.com"
```

## 4 Порядок взаимодействия с этим репозиторием
### 4.1 Начало взаимодействия
1. После создания ветки для индивидуальных занятий (об этом сообщу лично) нужно форкнуть (скопировать к себе на GitHub) этот репозиторий
![fork-cpp-lessons-1](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-1.png)

Убираем галочку в графе "Copy the main branch only"
![fork-cpp-lessons-2](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-2.png)

2. Загрузить форкнутый репозиторий к себе на компьютер при помощи команды

```
git clone <SSH-key>
```

![fork-cpp-lessons-3](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-3.png)
![fork-cpp-lessons-4](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-4.png)

3. Перейти в директорию с проектом

```
cd cpp-lessons
```

4. Перейти в свою рабочую ветку 

```
git checkout <your-branch>
```

После этой команды название ветки в скобках должно измениться с `main` на `your-branch`.

![fork-cpp-lessons-5](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-5.png)

### 4.2 Отправка работы на проверку
1. После выполнения задания коммитим изменения и отправляем их в **свой, форкнутый** репозиторий на GitHub.  
Для этого, находясь в директории с локальным репозиторием пишем команды

```
git add .
git commit -m "Любое информативное сообщение, отражающее суть внесенных изменений"
git push -u origin название_ветки
```

2. Переходим на GitHub, в свой репозиторий, и создаем pull request (запрос на вытягивание/слияние) как на скриншоте.
![fork-cpp-lessons-6](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-6.png)
> [!IMPORTANT]
> Выбираем одноименную ветку с вашей. В другие ветки делать запрос не нужно.

3. Ждем обратной связи касательно отправленного решения задачи.
![fork-cpp-lessons-7](https://raw.githubusercontent.com/Seredenko-V/cpp-lessons/main/tutorial-screens/fork-cpp-lessons-7.png)

