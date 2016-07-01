#ifndef IDRANGEJUGE__HPP
#define IDRANGEJUGE__HPP
#include <vector>
//企业类型
enum EntType{
	ENT_TYPE_INIT=0,
	ENT_TYPE_A,
	ENT_TYPE_B,
	ENT_TYPE_C,
	ENT_TYPE_OTHER
};

//对象类型
enum ObjType{
	OBJ_TYPE_INIT = 0,
	OBJ_TYPE_APP,
	OBJ_TYPE_USER,
	OBJ_TYPE_GROUP,
	OBJ_TYPE_OTHER
};

//获取企业类型
inline EntType GetEntType(int64 EntID){
	//右移56位等价于java中的无符号右移运算符>>>
	uint64 entSign = ((uint64)EntID>>56);
	if(0<=entSign && entSign<31)//最高字节0~31
		return ENT_TYPE_A;
	else if(64<=entSign && entSign<71)//最高字节64~71
		return ENT_TYPE_B;
	else if( 127 == entSign)
		return ENT_TYPE_C;//最高字节127
	else
		return ENT_TYPE_OTHER;//其他情况
}
//根据targetid获取entID
inline int64 GetObjectEntID(int64 targetID){
	int64 entID = 0;
	EntType entType = ENT_TYPE_INIT;
	
	//获取企业类型
	entType = GetEntType(targetID);
	switch(entType){
	case ENT_TYPE_A:
		{
		   entID = ((uint64)targetID>>24);//前5个字节为企业ID
		   break;
		}
	case ENT_TYPE_B:
		{
		   entID = ((uint64)targetID>>32)<<8;//前4个字节为企业ID部分，然后补一个字节，为企业ID
		   break;
		}
	case ENT_TYPE_C:
	   {
		   entID=((uint64)targetID>>40)<<16;//前3个字节为企业ID部分，然后补2个字节，为企业ID
		   break;
	   }
  }
  return entID;
}
//获取企业对象id范围
inline std::vector<int64> GetObjetRange(int64 objectID,ObjType objType)
{
	std::vector<int64> range;
	//应用、用户、群ID范围，升一个字节在原字节范围上*256，即四字节范围，在三字节范围上*256，为四字节范围
	EntType entType= GetEntType(objectID<<24);//企业ID都只占5字节，补3字节凑8字节去判断企业类型。
	int64 begin = 0;
	int64 end   = 0;
	int64 minAppId=0x15F90;//90000
    int64 maxAppId = 0x1869F;//99999
    int64 maxUserId = 0x7FFFFF;//8388607
    int64 maxGroupId = 0xFFFFFF;//1677721

	switch(entType){
		case ENT_TYPE_A:
	    {
			//企业ID左移三字节（占5字节） + 原始范围
			if(objType == OBJ_TYPE_APP){
				begin =(objectID<<24)+minAppId;
				end  =(objectID<<24)+maxAppId;
			}else if(objType == OBJ_TYPE_USER){
				begin =(objectID<<24)+maxAppId+1;
				end =(objectID<<24)+maxUserId;
			}else if(objType == OBJ_TYPE_GROUP){
				begin =(objectID<<24)+maxUserId+1;
				end =(objectID<<24)+maxGroupId;
			}
			break;
		}
		case ENT_TYPE_B:
		{
			//企业ID左移一字节（去一字节），右移4字节（占4字节） + 原始范围右移1字节
			if( objType == OBJ_TYPE_APP){
				begin =((objectID>>8)<<32)+(minAppId<<8);
				end   =((objectID>>8)<<32)+(maxAppId<<8);
			}else if(objType==OBJ_TYPE_USER){
				begin =((objectID>>8)<<32)+(maxAppId<<8)+1;
				end   =((objectID>>8)<<32)+(maxUserId<<8);
			}else if(objType==OBJ_TYPE_GROUP){
				begin =((objectID>>8)<<32)+(maxUserId<<8)+1;
				end   =((objectID>>8)<<32)+(maxGroupId<<8);
			}
			break;
		}
		case ENT_TYPE_C:
		{
			//企业ID左移2字节（去2字节），右移5字节（占3字节） + 原始范围右移2字节
			if(objType==OBJ_TYPE_APP){
				begin =((objectID>>16)<<40)+(minAppId<<16);
				end =((objectID>>16)<<40)+(maxAppId<<16);
			}else if(objType==OBJ_TYPE_USER){
				//begin =((objectID>>16)<<40)+(maxAppId<<16)+1;
				//end   =((objectID>>16)<<40)+(maxUserId<<16);
				begin = 9151315548882010113;
				end   = 9151316092084224000;
			}else if(objType==OBJ_TYPE_GROUP){
				begin =((objectID>>16)<<40)+(maxUserId<<16)+1;
				end   =((objectID>>16)<<40)+(maxGroupId<<16);
			}
			break;
		}
	}
	range.push_back(begin);
	range.push_back(end);
	return range;
}
inline bool JudgeRange(int64 targetID,ObjType objType){
		bool inside = false;
		int64 entID= GetObjectEntID(targetID);
		std::vector<int64> range = GetObjetRange(entID,objType);
		if(targetID>=range[0] && targetID <= range[1]){
			inside = true;
		}
		return inside;
	}
inline bool isUser(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_USER);
}

inline bool isGroup(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_GROUP);
}

inline bool isApp(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_APP);
}

inline bool isSameEnterpriseUser(int64 userID, int64 targetID){
	return (GetObjectEntID(userID) == GetObjectEntID(targetID));
}
#define	IS_MSG_USER		isUser
#define IS_MSG_GROUP	isGroup
#define IS_MSG_APP		isApp
#define IS_SAME_ENTERUSER isSameEnterpriseUser
#endif
