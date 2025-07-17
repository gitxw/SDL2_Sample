#pragma once

/// <summary>
/// 用户数据
/// </summary>
class T004_UserData {
public:
    // 鼠标点
    int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

    bool isDrawPoint = false; // 是否画点
    bool isDrawLine = false; // 是否画线
    bool isDrawRect = false; // 是否画矩形
};
