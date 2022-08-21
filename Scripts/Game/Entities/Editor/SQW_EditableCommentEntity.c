[EntityEditorProps(category: "GameScripted/Utility", description: "Editor comment, for leaving notes in the editor", sizeMin: "-1 -1 -1", sizeMax: "1 1 1", visible: false, dynamicBox: true)]
class SQW_EditableCommentEntityClass : CommentEntityClass
{
}

class SQW_EditableCommentEntity : CommentEntity
{
	//Parent variables
	//string m_Comment;
	//vector m_Color;
	vector m_vLocation = {60,1,70};
	
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
	void SetColor(vector col)
	{
		m_Color = col;
	}

	//------------------------------------------------------------------------------------------------
	/*
	void DrawComment()
	{
		float textWidthScale = 0.7;
			
		ShapeFlags flags = ShapeFlags.ONCE | ShapeFlags.TRANSP;
		if (m_VisibleOverall)
			flags |= ShapeFlags.NOZBUFFER;
		if (m_Transparency > 0)
			flags |= ShapeFlags.TRANSP;
					
		int dtFlags = DebugTextFlags.CENTER | DebugTextFlags.ONCE;
				
		float size = m_Size;
		int bgColor = ARGBF(0, 0, 0, 0);
		DebugTextWorldSpace.CreateInWorld(GetWorld(), m_Comment, dtFlags, m_vLocation, size, ARGBF(1 - m_Transparency, m_Color[0], m_Color[1], m_Color[2]), bgColor);
	}
	*/
			
};

