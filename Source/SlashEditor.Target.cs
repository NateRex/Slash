// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SlashEditorTarget : TargetRules
{
	public SlashEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Slash" } );
	}
}
