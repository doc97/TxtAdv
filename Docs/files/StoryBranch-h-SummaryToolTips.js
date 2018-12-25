NDSummary.OnToolTipsLoaded("File:StoryBranch.h",{129:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype129\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">StoryBranch</div></div></div><div class=\"TTSummary\">Represents one storyline in the game.</div></div>",131:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype131\" class=\"NDPrototype NoParameterForm\">StoryBranch()</div><div class=\"TTSummary\">Creates an anonymous, parentless branch.</div></div>",132:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype132\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">StoryBranch(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">name</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a named, parentless branch.</div></div>",133:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype133\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> AddPoint(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">StoryPoint&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">point</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",134:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype134\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> AddPoint(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">text,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\">vector&lt;std::<span class=\"SHKeyword\">function</span>&lt;std::<span class=\"SHKeyword\">string</span>()&gt;&gt;&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">expr,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\">vector&lt;std::shared_ptr&lt;ResponseHandler&gt;&gt;&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">handlers</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Add a StoryPoint by using its parameters</div></div>",135:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype135\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> Next()</div><div class=\"TTSummary\">Advances to the next point in the story.</div></div>",136:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype136\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> Prev()</div><div class=\"TTSummary\">Reverses to the previous point in the story.</div></div>",137:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype137\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> SetCurrentPoint(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">unsigned</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">index</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Moves to a certain point in the story line.</div></div>",138:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype138\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> SetParentBranch(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">StoryBranch&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">parent</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">The StoryBranch which will become the parent</div></div>",139:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype139\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> UnsetParentBranch()</div><div class=\"TTSummary\">Makes the branch parentless.</div></div>",140:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype140\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> GetName() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">The name of the branch, &quot;&quot; if no name has been set</div></div>",171:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype171\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">StoryPoint* GetPointAt(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">unsigned</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">int</span>&nbsp;</td><td class=\"PName last\">index</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div></div>",172:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype172\" class=\"NDPrototype NoParameterForm\">StoryPoint* GetHead() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the current StoryPoint.</div></div>",173:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype173\" class=\"NDPrototype NoParameterForm\">StoryBranch* GetParentBranch() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">A pointer to the parent branch.</div></div>",144:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype144\" class=\"NDPrototype NoParameterForm\">size_t Length() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">The number of story points in this branch</div></div>",145:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype145\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> Empty() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">True if the Length of this branch is 0</div></div>"});