[EntityEditorProps(category: "GameScripted/Utility", description: "Editor comment, for leaving notes in the editor", sizeMin: "-1 -1 -1", sizeMax: "1 1 1", visible: false, dynamicBox: true)]
class SQW_EditableCommentEntityClass : CommentEntityClass
{
}

class SQW_EditableCommentEntity : CommentEntity
{
	//Parent variables
	//string m_Comment;
	//vector m_Color;
	
	
	//------------------------------------------------------------------------------------------------
	/*!
	set comment 
	\param comment string
	*/
	void SetComment(string comment)
	{
	m_Comment = comment;
	}

	
	//------------------------------------------------------------------------------------------------
	/*!
	set comment color
	\param Color
	*/
	void SetColor(Color col)
	{
		m_Color = col;
	}
	
	
	
};

