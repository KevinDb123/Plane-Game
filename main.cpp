#include <windows.h>//共600行左右
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
class Plane {
private:
    int x, y;
    IMAGE plane_img;

public:
    int life;
    int img_pic;//0是第一张me1,1是第二张me2
    bool is_dead;
    Plane() : x(240), y(600),life(5),img_pic(0),is_dead(false) {
        loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me1.png"));
    }
    ~Plane() {
        std::cout << "Game Over" << std::endl;
    }
    void Move(int new_x, int new_y) {
        x = new_x;
        y = new_y;
    }
    void change_pic() {
        switch (life) {
        case 5:
            if (img_pic == 0) {
                loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me2.png"));
                img_pic = 1;
            }
            else {
                loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me1.png"));
                img_pic = 0;
            }
            break;
        case 4:
            loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me_destroy_1.png"));
            break;
        case 3:
            loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me_destroy_2.png"));
            break;
        case 2:
            loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me_destroy_3.png"));
            break;
        case 1:
            loadimage(&plane_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\me_destroy_4.png"));
            break;
        default:
            is_dead = true;
            break;
        }
    }
    void Draw() const {
        putimage(x - 55, y - 45, &plane_img,SRCAND);
    }
    int GetX() const { return x; }
    int GetY() const { return y; }
};
class Bullet {
private:
    int x, y;
    int speed;
    IMAGE bullet_img;

public:
    bool isActive;

    Bullet(int x, int y) : x(x), y(y), speed(10), isActive(true) {
        loadimage(&bullet_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\bullet1.png"));
    }

    ~Bullet() {
        std::cout << "Bullet Destroy" << std::endl;
    }

    void Move() {
        y -= speed;
        if (y < 0) {
            isActive = false;
        }
    }

    void Draw() const {
        putimage(x - 5, y, &bullet_img,SRCAND);
    }

    int Get_bullet_y() const { return y; }
    int Get_bullet_x() const { return x; }
};
class Enemy {
protected:
    int x, y, life,speed;
    IMAGE enemy_img;
public:
    int width, height;
    bool is_dead;
    int score;
    int status;//6 5 4 3 2 1 0 -1
    Enemy(int enemy_x, int enemy_y, int enemy_speed, int enemy_life,int enemy_score,int enemy_width,int enemy_height)
        : x(enemy_x), y(enemy_y), speed(enemy_speed), life(enemy_life),width(enemy_width),height(enemy_height), is_dead(false),score(enemy_score),status(6) {
    }
    void Draw() {
        putimage(x, y, &enemy_img,SRCAND);
    }
    void Move() {
        y = y + speed;
        change_status();
    }
    void Life_change(int change_num){//change_num可以正可以负
        life += change_num;
    }
    virtual void change_status() = 0;
    virtual void changeImg() = 0;
    int Get_X() const { return x; }
    int Get_Y() const { return y; }
};
class Enemy1:public Enemy {
public:
    Enemy1(int enemy_x,int enemy_y):Enemy(enemy_x,enemy_y,5,50,5,57,43){
        loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1.png"));
        std::cout << "Create a small_enemy" << std::endl;
    }
    ~Enemy1() {
        std::cout << "Small Enemy Destroy" << std::endl;
    }
    void change_status() override{
        if (life > 0 && y < 700) {
            is_dead = false;
        }
        else {
            is_dead = true;
        }
    }
    void changeImg() override{
        switch (status) {
            case 6:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1.png"));
                break;
            case 5:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1_down1.png"));
                break;
            case 4:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1_down2.png"));
                break;
            case 3:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1_down3.png"));
                break;
            case 2:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy1_down4.png"));
                break;
            default:
                is_dead = true;
                break;
        }
    }
};
class Enemy2 :public Enemy {
public:
    Enemy2(int enemy_x, int enemy_y) :Enemy(enemy_x, enemy_y, 4, 100,8,69,99) {
        loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2.png"));
        std::cout<<"Create a Middle_enemy"<<std::endl;
    }
    ~Enemy2(){
        std::cout<<"Middle Enemy Destroy" << std::endl;
    }
    void change_status() override {
        if (life > 0 && y < 700) {
            is_dead = false;
        }
        else {
            is_dead = true;
        }
    }
    void changeImg() override{
        switch (status) {
            case 6:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2.png"));
                break;
            case 5:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2_down1.png"));
                break;
            case 4:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2_down2.png"));
                break;
            case 3:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2_down3.png"));
                break;
            case 2:
                loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy2_down4.png"));
                break;
            default:
                is_dead = true;
                break;
        }
    }
};
class Enemy3 :public Enemy {
public:
    Enemy3(int enemy_x, int enemy_y) :Enemy(enemy_x, enemy_y, 3, 100,15,169,258){
        loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_n1.png"));
        std::cout << "Create a Big_enemy" << std::endl;
    }
    ~Enemy3() {
        std::cout << "Big Enemy Destroy" << std::endl;
    }
    void change_status() override {
        if (life > 0 && y < 700) {
            is_dead = false;
        }
        else {
            is_dead = true;
        }
    }
    void changeImg() override{
        switch (status) {
        case 6:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3.png"));
            break;
        case 5:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down1.png"));
            break;
        case 4:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down2.png"));
            break;
        case 3:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down3.png"));
            break;
        case 2:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down4.png"));
            break;
        case 1:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down5.png"));
            break;
        case 0:
            loadimage(&enemy_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\enemy3_down6.png"));
            break;
        default:
            is_dead = 1;
            break;
        }
    }
};
class Bullet_supply {
private:
    int x, y,speed;
    IMAGE bs_img;
public:
    bool is_Active;
    Bullet_supply(int bs_x,int bs_y):x(bs_x),y(bs_y),speed(4),is_Active(1){
        loadimage(&bs_img, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\bullet_supply.png"));
    }
    ~Bullet_supply() {
        std::cout << "Bullet_supply Destroyed!" << std::endl;
    }
    void Draw(){
        putimage(x, y, &bs_img,SRCAND);
    }
    void Move() {
        y = y + speed;
    }
    int Get_X() const {
        return x;
    }
    int Get_Y() const {
        return y;
    }
};
class Background {
public:
    IMAGE bg_img1, bg_img2;
    void Draw(int x){
        loadimage(&bg_img1, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\background.png"));
        loadimage(&bg_img2, _T("C:\\Users\\23815\\Desktop\\Game1\\Game1\\res\\background.png"));
        putimage(0, x, &bg_img1);
        putimage(0, x + 700, &bg_img2);
    }

};
void DrawBackground(int);
void DrawPause(int);
void DrawStartScreen();
void DrawEnd(int);
void PrintText(int, int, int);
void Draw_bullet(std::vector<Bullet>&);
void Draw_enemies(std::vector<Enemy*>&);
void Draw_Bullet_supply(std::vector<Bullet_supply>&);
void Check_supply(std::vector<Bullet_supply>&, std::vector<Bullet>&, int&);
void Check_enemy_bullet(std::vector<Enemy*>&, std::vector<Bullet>&, int&);
void Check_enemy_plane(std::vector<Enemy*>&, Plane&);
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    initgraph(480, 700);
    HWND hWnd = GetHWnd();
    SetWindowText(hWnd, _T("飞机大战"));
    int score = 0;
    int life = 5;
    int bulletCounts = 50;
    int bullet_flag = 1;
    int enemy_x_rand;
    int bs_x_rand;
    BeginBatchDraw();
    Plane plane;
    std::vector<Bullet> bullets;
    std::vector<Enemy*> enemies;
    std::vector<Bullet_supply> bullet_supplies;
    int bulletSpawnTimer = 0;
    int enemyCreateTimer = 0;
    int BSCreateTimer = 0;
    int changePicTimer = 0;
    const int BULLET_SPAWN_INTERVAL = 15;
    const int ENEMY_CREATE_INTERVAL = 60;
    const int BS_CREATE_INTERVAL = 150;
    const int CHANGE_PIC_INTERVAL = 15;
    int x = -700;
    int random_enemy = 0;//0表示小飞机，1表示中飞机，2表示大飞机
    MOUSEMSG msg;
    DrawStartScreen();
    FlushBatchDraw();
    while (true) {
        MOUSEMSG msg = GetMouseMsg(); // 获取鼠标事件
        if (msg.uMsg == WM_LBUTTONDOWN) { // 如果是左键按下
            break;
        }
    }
    DrawBackground(x);
    PrintText(score,life,bulletCounts);
    while (true) {
        life = plane.life;
        while (MouseHit()){
            msg = GetMouseMsg();
            if (msg.uMsg == WM_MOUSEMOVE) {
                plane.Move(msg.x, 550);
            }
        }
        DrawBackground(x);
        x += 5;
        if (x >= -4) {
            x -= 700;
        }
        bulletSpawnTimer++;
        if (bulletSpawnTimer >= BULLET_SPAWN_INTERVAL && bullet_flag) {
            bullets.push_back(Bullet(plane.GetX(), plane.GetY() - 45));
            bulletSpawnTimer = 0;
            bulletCounts--;
            if (bulletCounts == 0) {
                bullet_flag = 0;
            }
        }
        Draw_bullet(bullets);
        enemyCreateTimer++;
        if (enemyCreateTimer >= ENEMY_CREATE_INTERVAL) {
            random_enemy = rand() % 10;
            if(random_enemy<5){
                enemy_x_rand = rand() % 423;
                enemies.push_back(new Enemy1(enemy_x_rand, -50));
            }else if (random_enemy < 8) {
                enemy_x_rand = rand() % 411;
                enemies.push_back(new Enemy2(enemy_x_rand, -100));
            }else{
                enemy_x_rand = rand() % 311;
                enemies.push_back(new Enemy3(enemy_x_rand, -300));
            }
            enemyCreateTimer = 0;
        }
        Draw_enemies(enemies);
        BSCreateTimer++;
        if (BSCreateTimer >= BS_CREATE_INTERVAL) {
            bs_x_rand = rand() % 422;
            bullet_supplies.push_back(Bullet_supply(bs_x_rand, 0));
            BSCreateTimer = 0;
        }
        Draw_Bullet_supply(bullet_supplies);
		Check_supply(bullet_supplies, bullets, bulletCounts);
        Check_enemy_bullet(enemies,bullets,score);
        Check_enemy_plane(enemies,plane);
        PrintText(score, life, bulletCounts);
        changePicTimer++;
        if (changePicTimer >= CHANGE_PIC_INTERVAL) {
            plane.change_pic();
            changePicTimer = 0;
        }
        plane.Draw();
        FlushBatchDraw();
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // 检测 ESC 键是否按下
            DrawPause(x);
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                Sleep(10);
            }
            
            // 进入暂停状态
            while (true) {
                if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    // 等待按键释放，避免快速反复触发
                    while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                        Sleep(10);
                    }
                    break; // 退出暂停状态
                }

                // 这里可以执行暂停期间的其他逻辑
                Sleep(10); // 降低 CPU 占用
            }

            // 此时已退出暂停状态
        }
        Sleep(10);
        if (plane.life <= 0 || bulletCounts <= 0) {
            DrawEnd(score);
            while (true) {
                MOUSEMSG msg1 = GetMouseMsg();
                if (msg1.uMsg == WM_LBUTTONDOWN) {
                    break;
                }
            }
            break;
        }
    }

    EndBatchDraw();
    closegraph();
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		delete* it;
	}
	for (auto it = bullets.begin();it != bullets.end();++it) {
		delete& (*it);
	}
    return 0;
}
void DrawBackground(int x) {
    Background bg;
    bg.Draw(x);
}
void DrawPause(int x) {
    FlushBatchDraw();
    BeginBatchDraw();
    cleardevice();
    DrawBackground(x); // 绘制背景
    settextcolor(RED); // 设置文字颜色为黑色
    setbkmode(TRANSPARENT);
    settextstyle(30, 15, _T("黑体"));
    outtextxy(170, 300, _T("游戏中止"));
    outtextxy(150, 350, _T("按Esc继续游戏"));
    FlushBatchDraw();
}
void DrawStartScreen() {
    DrawBackground(-700);

    // 绘制标题
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    settextstyle(60, 0, _T("仿宋"));
    outtextxy(110, 150, _T("飞机大战"));
    settextstyle(30, 0, _T("仿宋"));
    outtextxy(110, 350, _T("点击任意位置开始..."));
}
void PrintText(int score, int life, int bullets) {
    settextcolor(RED);
    setbkmode(OPAQUE);
    setbkcolor(WHITE);
    settextstyle(30, 15, _T("仿宋"));
    std::wstring score_str = L"Score: " + std::to_wstring(score);
    std::wstring life_str = L"Life: " + std::to_wstring(life);
    std::wstring bullets_str = L"Bullets: " + std::to_wstring(bullets);
    outtextxy(30, 20, score_str.c_str());
    outtextxy(30, 60, life_str.c_str());
    outtextxy(30, 100, bullets_str.c_str());
    setlinecolor(RED);
    setlinestyle(PS_SOLID, 5);
    line(0, 500, 480, 500);
}
void Draw_bullet(std::vector<Bullet>& bullets) {
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->Move();
        if (it->isActive) {
            it->Draw();
            ++it;
        }
        else {
            it = bullets.erase(it);
        }
    }
}
void Draw_enemies(std::vector<Enemy*>& enemies) {
    for (auto it = enemies.begin();it != enemies.end();) {
        (*it)->Move();  // 调用 Move 方法
        if (!(*it)->is_dead) {
            (*it)->Draw();  // 调用 Draw 方法
            ++it;
        }
        else {
            delete* it;
            it = enemies.erase(it);
        }
    }
}
void Draw_Bullet_supply(std::vector<Bullet_supply>& bullet_supply) {
    for (auto it = bullet_supply.begin();it != bullet_supply.end();) {
        it->Move();
        if (it->is_Active) {
            it->Draw();
            ++it;
        }
        else {
            it = bullet_supply.erase(it);
        }
    }
}
void Check_supply(std::vector<Bullet_supply>& bullet_supply, std::vector<Bullet>& bullets, int& BulletCounts) {
    auto it = bullet_supply.begin();
    while (it != bullet_supply.end()) {
        bool erased = false;
        auto bullet = bullets.begin();
        while (bullet != bullets.end()) {
            if (bullet->Get_bullet_x() > it->Get_X() && bullet->Get_bullet_x() < it->Get_X() + 58 &&
                bullet->Get_bullet_y() > it->Get_Y() && bullet->Get_bullet_y() < it->Get_Y() + 88) {
                it = bullet_supply.erase(it);
                bullet = bullets.erase(bullet);
                BulletCounts += 10;
                erased = true;
                break; // 跳出内层循环
            }
            else {
                ++bullet;
            }
        }
        if (!erased) {
            ++it; // 如果没有删除元素，才递增迭代器
        }
    }
}
void Check_enemy_bullet(std::vector<Enemy*>& enemies, std::vector<Bullet>& bullets, int& score) {
    auto it = enemies.begin();
    while (it != enemies.end()) {
        bool erased = false;
        auto bullet = bullets.begin();
        while (bullet != bullets.end()) {
            if (bullet->Get_bullet_x() > (*it)->Get_X() && bullet->Get_bullet_x() < (*it)->Get_X() + (*it)->width &&
                bullet->Get_bullet_y() > (*it)->Get_Y() && bullet->Get_bullet_y() < (*it)->Get_Y() + (*it)->height) {
                score += (*it)->score;
                (*it)->status -= 2;
                (*it)->changeImg();
                if ((*it)->is_dead) {
                    delete* it;
                    it = enemies.erase(it);
                    erased = true;
                }
                bullet = bullets.erase(bullet);
                break;
            }
            else {
                ++bullet;
            }
        }
        if (!erased) {
            ++it;
        }
    }
}
void Check_enemy_plane(std::vector<Enemy*>& enemies, Plane& plane) {
    for (auto it = enemies.begin();it != enemies.end();) {
        if ((*it)->Get_X() <= plane.GetX() + 102 && (*it)->Get_X() >= plane.GetX() - (*it)->width
            && plane.GetY() >= (*it)->Get_Y() - 126 && plane.GetY() <= (*it)->Get_Y() + (*it)->height) {
            delete* it;
            it = enemies.erase(it);
            plane.life--;
        }
        ++it;
    }
}
void DrawEnd(int score) {
    cleardevice();
    FlushBatchDraw();
    BeginBatchDraw();
    DrawBackground(-700);
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    settextstyle(50, 0, _T("黑体"));
    outtextxy(100, 200, _T("游戏结束")); // 显示“游戏结束”
    std::wstring scoreStr = L"最终得分: " + std::to_wstring(score);
    outtextxy(100, 250, scoreStr.c_str()); // 显示最终得分
    settextstyle(20, 0, _T("仿宋"));
    outtextxy(150, 350, _T("点击可退出游戏"));
    FlushBatchDraw();
}