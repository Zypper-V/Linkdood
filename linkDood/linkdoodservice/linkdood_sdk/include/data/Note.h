#pragma once
namespace service{
	struct _Note__isset{
		_Note__isset(void):type(false),isReminder(false),isArchive(false),rmdTime(false),
		id(false),lastChgTime(false),sendUserId(false),targetId(false),key(false),title(false),
		content(false){}
		bool type;
		bool isReminder;
		bool isArchive;
		bool rmdTime;
		bool id;
		bool lastChgTime;
		bool sendUserId;
		bool targetId;
		bool key;
		bool title;
		bool content;
	};
	class Note{
	public:
		Note() :type(0), isReminder(0), isArchive(0), rmdTime(0),
			id(0), lastChgTime(0), sendUserId(0), targetId(0){}
		virtual ~Note(void){}
		void init(void){}
		void __set_type(const int8 val){
			type = val;
			__isset.type = true;
		}
		void __set_isReminder(const int8 val){
			isReminder = val;
			__isset.isReminder = true;
		}
		void __set_isArchive(const int8 val){
			isArchive = val;
			__isset.isArchive = true;
		}
		void __set_rmdTime(const int64 val){
			rmdTime = val;
			__isset.rmdTime = true;
		}
		void __set_id(const int64 val){
			id = val;
			__isset.id = true;
		}
		void __set_lastChgTime(const int64 val){
			lastChgTime = val;
			__isset.lastChgTime = true;
		}
		void __set_sendUserId(const int64 val){
			sendUserId = val;
			__isset.sendUserId = true;
		}
		void __set_targetId(const int64 val){
			targetId = val;
			__isset.targetId = true;
		}
		void __set_key(const std::string& val){
			key = val;
			__isset.key = true;
		}
		void __set_title(const std::string& val){
			title = val;
			__isset.title = true;
		}
		void __set_content(const std::string& val){
			content = val;
			__isset.content = true;
		}
		bool operator == (const Note& rhs)const {
			if (type != rhs.type)
				return false;
			if (isReminder != rhs.isReminder)
				return false;
			if (isArchive != rhs.isArchive)
				return false;
			if (rmdTime != rhs.rmdTime)
				return false;
			if (id != rhs.id)
				return false;
			if (lastChgTime != rhs.lastChgTime)
				return false;
			if (sendUserId != rhs.sendUserId)
				return false;
			if (targetId != rhs.targetId)
				return false;
			if (key != rhs.key)
				return false;
			if (title != rhs.title)
				return false;
			if (content != rhs.content)
				return false;
			return true;
		}
		int8 type;
		int8 isReminder;
		int8 isArchive;
		int64 rmdTime;
		int64 id;
		int64 lastChgTime;
		int64 sendUserId;
		int64 targetId;
		std::string key;
		std::string title;
		std::string content;
		_Note__isset __isset;
 };
}