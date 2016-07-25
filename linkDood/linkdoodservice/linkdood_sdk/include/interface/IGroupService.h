#pragma once
#include "../data/ErrorInfo.hpp"
#include "../data/Group.h"
#include"../data/packet.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>
namespace service{

    namespace sdk{
        class SdkChannel;
    }
    class IGroupService {
    public:
        /************************************************************************
        * @brief init
        * @description: ��ʼ��GroupService��
        * @param[in] channel ����SdkChannel��ʵ�������ڵ���SDK�ӿ�
        * @return:	bool �ɹ�:true, ʧ��:false
        ************************************************************************/
        virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

        /************************************************************************
        * @brief createGroup
        * @description: ����Ⱥ
        * @param[in] level ����Ⱥ�ȼ�
        * @param[in] name ����Ⱥ����
        * @param[in] members   ����Ⱥ��Ա
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void createGroup(
            int level, std::string& name, std::vector<int64>& members, std::function<void(ErrorInfo& info, int64 &res)> await) = 0;

        /************************************************************************
        * @brief addGroup
        * @description: ��Ⱥ
        * @param[in] groupid ����Ⱥid
        * @param[in] verify_info ������֤��Ϣ
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void addGroup(
            int64 groupid, std::string& verify_info, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief removeGroup
        * @description: ��ɢȺ
        * @param[in] type ������������
        * @param[in] groupid ����Ⱥid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void removeGroup(
            int type, int64 groupid, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief transferGroup
        * @description: ת��Ⱥ
        * @param[in] groupid ����Ⱥid
        * @param[in] userid ������Ⱥ����id
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void transferGroup(
            int64 groupid, int64 userid, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief setGroupSet
        * @description: ����Ⱥ����
        * @param[in] groupid ����Ⱥid
        * @param[in] verify_type ������֤����
        * @param[in] is_allow �����Ƿ�������Ա�����û�
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void setGroupSet(
            int64 groupid, int8 verify_type, int8 is_allow, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief setGroupInfo
        * @description: ����Ⱥ��Ϣ
        * @param[in] group ����Ⱥ��Ϣ
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void setGroupInfo(
            Group group, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief getGroupList
        * @description: ��ȡȺ�б�
        ************************************************************************/
        virtual void getGroupList(void) = 0;

        /************************************************************************
        * @brief getGroupSet
        * @description: ��ȡȺ����
        * @param[in] groupid ����Ⱥid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void getGroupSet(
            int64 groupid, std::function<void(ErrorInfo& info,int8 verify_type,int8 is_allow)> await) = 0;

        /************************************************************************
        * @brief getGroupInfo
        * @description: ��ȡȺ��Ϣ
        * @param[in] groupid ����Ⱥid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void getGroupInfo(
            int64 groupid, std::function<void(ErrorInfo& info,Group group)> await) = 0;

        /************************************************************************
        * @brief inviteMember
        * @description: ����Ⱥ��Ա
        * @param[in] groupid ����Ⱥid
        * @param[in] members ������Ա����
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void inviteMember(
            int64 groupid,std::vector<int64> members,std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief removeMember
        * @description: �Ƴ�Ⱥ��Ա
        * @param[in] groupid ����Ⱥid
        * @param[in] userid ������Ҫ�Ƴ��ĳ�Աid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void removeMember(
            int64 groupid, int64 userid, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief setMemberInfo
        * @description: ����Ⱥ��Ա��Ϣ
        * @param[in] member ������Ա��Ϣ
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void setMemberInfo(
            User& member, std::function<void(ErrorInfo& info)> await) = 0;

        /************************************************************************
        * @brief getMemberInfo
        * @description: ��ȡȺ��Ա��Ϣ
        * @param[in] groupid ����Ⱥid
        * @param[in] userid ������Աid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void getMemberInfo(
            int64 groupid,int64 userid, std::function<void(ErrorInfo& info,User& member)> await) = 0;

        /************************************************************************
        * @brief getMemberList
        * @description: ��ȡȺ��Ա�б�
        * @param[in] groupid ����Ⱥid
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void getMemberList(
            int64 groupid, std::function<void(ErrorInfo& info, std::vector<std::shared_ptr<User> > members)> await) = 0;

        /************************************************************************
        * @brief getGroupFileList
        * @description: ��ȡȺ�ļ��б�
        * @param[in] groupid ����Ⱥid
        * @param[in] beginid ������ʼid
        * @param[in] count ��������
        * @param[in] flag ����ƫ�Ʊ�־0Ϊ����1Ϊ����
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void getGroupFileList(
            int64 groupid,int64 beginid,int count,int8 flag, std::function<void(ErrorInfo& info, std::vector<FileInfo> fileInfos)> await) = 0;

        /************************************************************************
        * @brief deleteGroupFile
        * @description: ɾ��Ⱥ�ļ�
        * @param[in] files ����Ⱥ�ļ�id
        * @param[in] await  �������ս����ص�
        ************************************************************************/
        virtual void deleteGroupFile(
            std::vector<int64>files, std::function<void(ErrorInfo& info)> await) = 0;

    };
    std::shared_ptr<IGroupService> getGroupInstance(void);
}
