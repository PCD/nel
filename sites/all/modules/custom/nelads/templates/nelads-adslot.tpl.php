<?php if (isset($wrapper_class) && $wrapper_class):?>
<div class="<?php print $wrapper_class;?>">
<?php endif;?>
<!--#nelads-block-<?php print $adslot;?>-start-->
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<script type="text/javascript">!function(a){Drupal.behaviors.neladsAdslot<?php print $adslot;?>={attach:function(d,o){a(".adslot_<?php print $adslot;?>",d).once("nelads",function(){var d=o.nelads.<?php print $adsvar;?>[Math.floor(Math.random()*o.nelads.<?php print $adsvar;?>.length)];a(".adsbygoogle.adslot_<?php print $adslot;?>").attr({"data-ad-client":d.ad_client,"data-ad-slot":d.ad_slot,"data-ad-format":d.ad_format}),(adsbygoogle=window.adsbygoogle||[]).push({})})}}}(jQuery);</script>
<ins class="adsbygoogle adslot_<?php print $adslot;?>" style="display:block"></ins>
<!--#nelads-block-<?php print $adslot;?>-end-->
<?php if (isset($wrapper_class) && $wrapper_class):?>
</div>
<?php endif;?>
