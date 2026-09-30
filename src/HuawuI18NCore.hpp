#pragma once

// Core REFramework Simplified Chinese dictionary reconstructed from the user's
// Huawu MHWILDS REFramework translation (v1.1.4 / Nightly 01240).
// Applied at ImGui render/measurement time so widget IDs and REFramework logic
// stay on the official 01424 code path.

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <string_view>

namespace huawu_i18n {
struct Entry { uint32_t hash; const char* text; };

constexpr uint32_t fnv1a32(std::string_view s) noexcept {
    uint32_t h = 0x811C9DC5u;
    for (unsigned char c : s) {
        h ^= static_cast<uint32_t>(c);
        h *= 0x01000193u;
    }
    return h;
}

inline constexpr std::array<Entry, 160> dict{{
    Entry{0x0027D873u, "让REF在未选中时变得透明。"},
    Entry{0x03E7D872u, "自由视角"},
    Entry{0x0532D6CFu, "禁用移动切换键"},
    Entry{0x0A6B8020u, "移动速度"},
    Entry{0x0BCD68FAu, "创建新的游戏资源"},
    Entry{0x0CC054BDu, "发生未知错误。"},
    Entry{0x0EC0331Du, "身体旋转速度"},
    Entry{0x10C31961u, "默认菜单按键：Insert"},
    Entry{0x10F4BB5Cu, "控制器旋转(右)"},
    Entry{0x12164A37u, "无已加载插件。"},
    Entry{0x13731364u, "这个设置会一直生效，无需点击上面的“启用”"},
    Entry{0x1595789Cu, "常规设置"},
    Entry{0x176D23A9u, "分辨率缩放"},
    Entry{0x18324804u, "开发者工具"},
    Entry{0x1A5EE459u, "设置"},
    Entry{0x1FB67EBAu, "进入Windows图形设置并禁用“硬件加速GPU调度”"},
    Entry{0x20B7BCF4u, "第一人称"},
    Entry{0x222870E5u, "资源管理器"},
    Entry{0x231DA0ACu, "上一个脚本错误: %s"},
    Entry{0x23581988u, "更改切换键"},
    Entry{0x280981D7u, "时间比例（持续）热键"},
    Entry{0x28ED6833u, "最近的松散文件"},
    Entry{0x2A52FD5Bu, "已使用MB:%.2f"},
    Entry{0x2A610338u, "Debug"},
    Entry{0x2AD8CDC5u, "上次报错时间: %.2f 秒前"},
    Entry{0x2B82EA75u, "UI透过"},
    Entry{0x2F02770Bu, "渲染分辨率: %d x %d"},
    Entry{0x2FB6EE50u, "垃圾收集类型"},
    Entry{0x303A7F58u, "旋转速度"},
    Entry{0x316B76F4u, "调试信息"},
    Entry{0x32FEAF9Eu, "GUI设置"},
    Entry{0x38AF419Fu, "没有运行时被加载。"},
    Entry{0x391028E3u, "无脚本加载。"},
    Entry{0x39176A50u, "将所有访问的文件记录到<游戏根目录>/reframework_accessed_files.txt"},
    Entry{0x3DF5ED3Bu, "%s 未加载: %s"},
    Entry{0x3F4A8054u, "脚本运行设置"},
    Entry{0x3F83E1F9u, "镜头偏移"},
    Entry{0x40732179u, "控制器方向(右)"},
    Entry{0x44102531u, "启动松散文件加载器"},
    Entry{0x449EA51Fu, "硬件调度中:%s"},
    Entry{0x44E37F5Du, "清理统计数据"},
    Entry{0x45E0711Au, "超宽:视野放大"},
    Entry{0x475365D4u, "类型名称"},
    Entry{0x4A70734Eu, "晕影亮度"},
    Entry{0x4C786FF5u, "使用自定义全局FOV视角"},
    Entry{0x4FCD899Fu, "没有脚本错误…牛逼！"},
    Entry{0x5222F487u, "搜索到的文件：%d"},
    Entry{0x52B9B61Au, "警告：已启用硬件加速GPU调度。这将导致游戏运行较慢。"},
    Entry{0x530C3C62u, "呼出调试控制台"},
    Entry{0x53A29683u, "强制旋转关节"},
    Entry{0x5473B285u, "插件"},
    Entry{0x55BC086Du, "界面显示/隐藏是否保存"},
    Entry{0x573D06FEu, "%s 未加载: %s 妹找着啊……"},
    Entry{0x5757C139u, "显示光标键"},
    Entry{0x58E096DEu, "关于"},
    Entry{0x594A391Eu, "渲染器"},
    Entry{0x5B7F2BB6u, "无法获取模块尺寸"},
    Entry{0x5BAA6196u, "REFramework设置"},
    Entry{0x6040061Eu, "已加载脚本:"},
    Entry{0x64215C53u, "桌面"},
    Entry{0x665A7F1Bu, "垃圾收集统计信息"},
    Entry{0x66A384CFu, "VR运行时间: %s"},
    Entry{0x69C88790u, "启用性能分析"},
    Entry{0x69FAD695u, "同步模式"},
    Entry{0x6AD9AA4Bu, "视角向上移动"},
    Entry{0x6C88A810u, "REFramework错误: %s"},
    Entry{0x6D6E30EBu, "垃圾收集模式"},
    Entry{0x6E56339Fu, "禁用晕影"},
    Entry{0x6FA5465Eu, "隐藏关节网"},
    Entry{0x76740405u, "勾选下面的“启用”来让设置生效。"},
    Entry{0x76848334u, "垃圾收集处理管理器"},
    Entry{0x76B3F342u, "隐藏GUI"},
    Entry{0x76E0BEE2u, "未知按键"},
    Entry{0x76FA66E1u, "VR"},
    Entry{0x77241CFEu, "让鼠标能够穿过REF界面点击到游戏内。"},
    Entry{0x77280449u, "移动速度补正"},
    Entry{0x79F88713u, "脚本设置界面"},
    Entry{0x7D45D8A5u, "减速移动"},
    Entry{0x7E68E0D9u, "禁用角色移动"},
    Entry{0x80F7C7AEu, "已加载插件："},
    Entry{0x828EEE4Cu, "平滑Y移动(VR)"},
    Entry{0x8297D1CAu, "视角向下移动"},
    Entry{0x8654C5D0u, "重载脚本"},
    Entry{0x86908B64u, "已加载的松散文件：%d"},
    Entry{0x870B80EDu, "按下任意键..."},
    Entry{0x8BD7B861u, "引擎信息"},
    Entry{0x8CB9AD17u, "透明"},
    Entry{0x8EB6BB6Bu, "次垃圾收集倍增"},
    Entry{0x8F38EF91u, "镜头速度"},
    Entry{0x8F517045u, "性能"},
    Entry{0x8F6B7A1Eu, "启用文件缓存"},
    Entry{0x90B402F3u, "控制器2"},
    Entry{0x91211C91u, "游戏资源显示距离"},
    Entry{0x91B40486u, "控制器1"},
    Entry{0x959A7458u, "将Lua错误记录到磁盘"},
    Entry{0x9815CE4Au, "原版作者：praydog\\n汉化作者：花舞汉化组\\n汉化版本：MHWILDS Ver1.1.4\\n对应内核：870709 (Nightly 01240)\\n反馈群：608262198"},
    Entry{0x9850A936u, "未绑定按键"},
    Entry{0x985EA3EEu, "最近访问的文件"},
    Entry{0x9BC2F940u, "菜单打开时绘制光标"},
    Entry{0x9C86E43Eu, "启用"},
    Entry{0xA16832D5u, "显示/隐藏热键"},
    Entry{0xA42B3F52u, "在剪接场景中显示"},
    Entry{0xA42BCD93u, "平滑XZ移动(VR)"},
    Entry{0xA4F03F58u, "镜头抖动"},
    Entry{0xA583A52Cu, "REFramework汉化版 MHWILDS Ver1.1.4"},
    Entry{0xA8169F3Au, "类型"},
    Entry{0xA9654F93u, "超宽:覆盖FOV"},
    Entry{0xAA980F74u, "LoosefileLoader松散文件加载器"},
    Entry{0xAB0749CFu, "记录访问的文件"},
    Entry{0xAE0D5CF3u, "控制器旋转(左)"},
    Entry{0xAEEB4931u, "分辨率可以在SteamVR中更改"},
    Entry{0xAF965C91u, "锁定视角"},
    Entry{0xB1DF526Au, "缓存点击数：%d"},
    Entry{0xB21CA2E1u, "字体大小"},
    Entry{0xB407A345u, "全局FOV"},
    Entry{0xB49B2BEDu, "运行脚本"},
    Entry{0xB525AE68u, "显示最近的文件"},
    Entry{0xB62B9FA8u, "图像显示设置"},
    Entry{0xB87D089Cu, "如果启用了“保存”选项，此菜单将在初始化后关闭。"},
    Entry{0xBA2A5D8Cu, "禁用位置切换键"},
    Entry{0xBB8BA9B2u, "旋转身体"},
    Entry{0xBBEA93EDu, "手柄死角"},
    Entry{0xBD3B2EF0u, "记录松散文件"},
    Entry{0xBF9B0F36u, "无法确定引擎版本。"},
    Entry{0xBFCE9925u, "禁用"},
    Entry{0xC044A7E3u, "绑定"},
    Entry{0xC0A18E47u, "主垃圾收集倍增"},
    Entry{0xC34D9D9Fu, "REFramework当前正在初始化……"},
    Entry{0xC89B38B3u, "场景设置"},
    Entry{0xC93DA77Au, "禁用闪光灯"},
    Entry{0xCB2D17E5u, "游戏资源显示"},
    Entry{0xCBFD4A30u, "mods初始化失败，原因: {}"},
    Entry{0xCD634039u, "垃圾收集预算"},
    Entry{0xD01ED170u, "清除现有缓存"},
    Entry{0xD2EAE519u, "请把 %s文件放入游戏目录，如果要使用 %s"},
    Entry{0xD420105Cu, "区块链可视化"},
    Entry{0xD5B0E348u, "VR具体设置"},
    Entry{0xD682EF63u, "灵感来自Kanan项目。"},
    Entry{0xD6C3EB56u, "快速移动"},
    Entry{0xD7B87681u, "未能成功加载。这个mod不起作用。"},
    Entry{0xD9EB7F3Fu, "使用应用程序时间刻度"},
    Entry{0xDB7A93A6u, "将松散文件记录加载到<游戏根目录>/reframework_loose_files.txt"},
    Entry{0xDCAF1594u, "错误："},
    Entry{0xE04485B0u, "超宽:启用垂直视野"},
    Entry{0xE1873AD6u, "时间比例（切换）热键"},
    Entry{0xE1E7485Bu, "转储SDK"},
    Entry{0xE1EC52DEu, "切换按键"},
    Entry{0xE74C7B6Eu, "视角"},
    Entry{0xE7D9FCC3u, "FOV倍增"},
    Entry{0xE8245E06u, "切换"},
    Entry{0xEAE6065Du, "未命中次数: %d"},
    Entry{0xEF30214Bu, "VR缩放"},
    Entry{0xF28B4983u, "超宽/纵横比修复"},
    Entry{0xF4AA2CA0u, "控制器方向(左)"},
    Entry{0xF606A315u, "当前FOV"},
    Entry{0xF9A267E1u, "2D UI缩放"},
    Entry{0xFC539F8Au, "警告："},
    Entry{0xFCA44895u, "%s 未加载: 未知错误"},
    Entry{0xFD0C7E3Eu, "时间尺度"},
    Entry{0xFF6EEAA7u, "FOV偏移"},
}};

inline const char* lookup(uint32_t hash) noexcept {
    const auto it = std::lower_bound(dict.begin(), dict.end(), hash,
        [](const Entry& e, uint32_t v) { return e.hash < v; });
    return (it != dict.end() && it->hash == hash) ? it->text : nullptr;
}

inline std::string_view translate(std::string_view text) noexcept {
    if (text.empty()) return text;
    if (const char* p = lookup(fnv1a32(text)); p != nullptr)
        return std::string_view{p};
    return text;
}

inline std::string_view translate(const char* begin, const char* end = nullptr) noexcept {
    if (begin == nullptr) return {};
    if (end == nullptr) end = begin + std::strlen(begin);
    return translate(std::string_view{begin, static_cast<size_t>(end - begin)});
}
} // namespace huawu_i18n
