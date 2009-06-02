#ifndef CHINESESTRINGS_H
#define CHINESESTRINGS_H
//#include "common.h"

//group name
#define smString "员工管理"
#define bmString "业务管理"
#define soString "店面运营"
#define logoffString "注销"
#define exitString "退出"
#define zeroSelectionWarning "您还没有选择选择任何列表项。"

//common strings
#define undefineStr "未定义"
#define scoreStr "分"
#define femaleStr "女"
#define maleStr "男"
#define cosmeticNameStr "Cosmetic（科思美）美容美发业运营系统"
#define emptyStr ""
#define staffEntraceStr "员工入口"
#define passwordStr "密码"
#define LoginStr "登录"
#define idStr "编号"
#define okStr "确定"
#define cancleStr "取消"
#define backStr "返回"
#define expandSideBarStr "展开侧边栏"
#define shrinkSideBarStr "收起侧边栏"
#define sexUndefinedStr "未设定"
#define sexMaleStr "男"
#define sexFemaleStr "女"
#define modifyWaring "未能成功修改，请重试。"
#define abandonModifyWarning "编辑部件中还有还有未提交的信息！\n放弃所做的修改?"
#define leftMark "“"
#define rightMark "”"
#define removeError "未能成功删除选定项目，请重试。"
#define choosePicStr "选择照片"
#define editStr "编辑"
#define submitStr "提交"
#define imageFileStr "图像文件(*.png *.jpg *.bmp *.gif)"
#define imageSizeWarning "非常抱歉，照片文件大小不能超过%1兆，请重新选择。"
#define percentStr "%"
#define moneyStr "￥"

//common mgnt strings
#define loginWindowTitle "登录错误"
#define loginErrorWarning "工号或密码错误，请重新输入。"

//staff mgnt strings
#define staffIDStr "工号"
#define staffNameStr "姓名"
#define staffSexStr "性别"
#define staffJobStr "职务"
#define staffLevelStr "级别"
#define staffStatusStr "状态"
#define staffRatingStr "客户满意度"
#define staffCellStr "手机"
#define staffPhoneStr "座机"
#define staffAddressStr "地址"
#define staffDescriptionStr "备注"
#define staffJobSalaryStr "职务工资"
#define staffLevelSalaryStr "级别工资"
#define staffProfitStr "提成(%)"
#define staffBrowseStr "员工浏览"
#define staffJobSettingStr "职务设置"
#define staffLevelSettingStr "级别设置"
//***********staff management message box strings
#define smEditModeWarning "目前处于新建员工状态，请完成后再修改资料。"
#define smEmptyNameWarnning "员工姓名不能留空， \n请返回并填写员工姓名。"
#define smRemoveStaffConfirm "确定删除选定员工“%1”？\n"\
	"如果员工离职，建议您更改该员工状态，而不是在系统中删除该员工。"
#define smAddStaffError "未能成功添加员工，请重试。"
#define smModifyStaffError "未能成功修改员工信息，请重试。"
#define smJobRemoveWarning \
	"未能成功删除，还有员工被设置为该职务。\n"\
	"建议你修改这些职务的参数，替代删除职务。"
#define smLevelRemoveWarning \
	"未能成功删除，还有员工被设置为该级别。\n"\
	"建议你修改这些级别的参数，替代删除级别。"
#define smChangePwSucces "你的密码已经成功更改。"
#define smChangePwFailure "原始密码错误，你的密码未能更改。"

//business management string
#define bmBrandStr "品牌"
#define bmBuysStr "进货"
#define bmCostStr "成本"
#define bmDescriptionStr "描述"
#define bmDiscountStr "折扣"
#define bmIdStr "代码"
#define bmNameStr "名称"
#define bmRatingStr "客户满意度"
#define bmPriceStr "价格"
#define bmSalesStr "总销售"
#define bmSpecificationStr "规格"
#define bmStocksStr "库存"
#define bmTypeStr "业务种类"
#define bmAdjustableStr "手动调整"
#define bmDualDiscountStr "重复折扣"
#define bmBusinessTypeCategoryStr "业务性质"
#define bmBusinessTypeDescriptionStr "描述"
#define bmBusinessTypeNameStr "种类名称"
#define bmBusinessTypeIdStr "代码"
#define bmDepositStr "充值类业务"
#define bmMemberCardStr "会员卡业务"
#define bmService "服务类业务"
#define bmSaleStr "商品类业务"
#define bmSpendingStr "日常开销"
#define bmSalaryStr "工资发放"
#define bmStockStr "进货"
#define bmReturnStockStr "退货"
#define bmBrowseStr "业务浏览"
#define bmTypeEditorStr "业务种类编辑"
//***********business management message box strings
#define bmModifyBusinessErrorStr "未能成功修改业务明细，请重试。"
#define bmAddBusinessErrorStr "未能成功添加新业务，请重试。"
#define bmRemoveBusinessConfirm \
	"业务“%1”及其所有营销记录都将被清空！\n确定贵公司不再提供该业务？"
#define bmBusinessEditModeWarning "新建的业务还未提交！\n放弃所做的编辑?"
#define bmBusinessCannotEditWarning \
	"您正在编辑新建业务，并且还未提交。无法进入业务修改模式。"
#define bmEmptyNameTypeWarnning "业务名称或种类不能留空，请返回并填写。"
#define bmTypeRemoveWaring "未能成功删除，可能是还有业务被设置为该种类。"

//customer management string
#define cmString "顾客管理"
#define cmCustomerBrowseStr "顾客浏览"
#define cmIdStr "顾客号"
#define cmNameStr "姓名"
#define cmSexStr "性别"
#define cmLevelStr "等级"
#define cmCellStr "手机"
#define cmPhoneStr "座机"
#define cmConsumeTimesStr "消费次数"
#define cmTotalConsumeStr "累积金额"
#define cmDepositStr "帐户余额"
#define cmAddressStr "地址"
#define cmDescriptionStr "备注"
#define cmCardIdStr "代码"
#define cmCardNameStr "名称"
#define cmCardRemainsStr "余额"

#define cmLevelEditorStr "顾客等级设置"
#define cmLevelIdStr "等级代码"
#define cmLevelNameStr "名称"
#define cmLevelRequireStr "消费要求"
#define cmLevelDiscountStr "享受折扣"
#define cmLevelDescriptionStr "备注"

#define cmCustomerEditModeWarning "新建的顾客还未提交！\n放弃所做的编辑?"
#define cmCustomerCannotEditWarning \
	"您正在新建顾客，并且还未提交。\n无法进入顾客修改模式。"
#define cmEmptyNameSexWarnning "顾客姓名和性别不能留空，请返回并填写。"
#define cmRemoveCustomerConfirm \
	"顾客“%1”及其所有消费记录都将被清空！确定不再保留该顾客？"
#define cmLevelRemoveWaring "未能成功删除，还有顾客位于当前等级。\n"\
	"建议你修改这些等级的参数，替代删除等级。"
#define cmModifyCustomerErrorStr "未能成功修改顾客资料，请重试。"
#define cmAddCustomerErrorStr "未能成功新建顾客，请重试。"


#define stString "库存管理"
#define rsString "报表系统"
#define cfString "系统设置"



#endif
