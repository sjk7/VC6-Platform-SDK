use employee
go


/****** Object:  Stored Procedure dbo.sp_AddEmployee    Script Date: 6/2/99 9:05:12 PM ******/
if exists (select * from sysobjects where id = object_id(N'[dbo].[sp_AddEmployee]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_AddEmployee]
GO

/****** Object:  Table [dbo].[employee]    Script Date: 6/2/99 9:05:12 PM ******/
if exists (select * from sysobjects where id = object_id(N'[dbo].[employee]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[employee]
GO

/****** Object:  Table [dbo].[employee]    Script Date: 6/2/99 9:05:13 PM ******/
CREATE TABLE [dbo].[employee] (
	[id] [int] IDENTITY (1, 1) NOT NULL ,
	[first_name] [char] (20) NULL ,
	[last_name] [char] (30) NOT NULL 
) ON [PRIMARY]
GO

SET QUOTED_IDENTIFIER  OFF    SET ANSI_NULLS  ON 
GO

/****** Object:  Stored Procedure dbo.sp_AddEmployee    Script Date: 6/2/99 9:05:14 PM ******/
CREATE PROCEDURE sp_AddEmployee @fname char(20), @lname char(20) AS
insert into employee values(@fname, @lname)
GO

SET QUOTED_IDENTIFIER  OFF    SET ANSI_NULLS  ON 
GO

