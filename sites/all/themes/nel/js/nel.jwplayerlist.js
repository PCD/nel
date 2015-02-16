/**
* JWPlayer Playlist plugin: simulate a dynamic playlist.
*
* @license http://creativecommons.org/licenses/by-nc-sa/3.0/ CC BY-NC-SA 3.0
*
* @version 0.1-rc1
* @modified moimikey
*/
(function (jwplayer) {
'use strict';
var template = function (player) {
var lastIndex = -1,
oldPlaylistLength,
playlist,
playlistIsModified = false;
player.onPlaylist(
/**
* Fired when a new playlist has been loaded into the player.
* Note this event is not fired as part of the initial playlist load (playlist is loaded when onReady is called).
*
* Reset playlist variables.
*/
function () {
playlist = player.getPlaylist();
oldPlaylistLength = playlist.length;
playlistIsModified = false;
for (var i = 0; i < playlist.length; i++) {
playlist[i].oldIndex = i;
}
});
player.onPlaylistItem(
/**
* Fired when the playlist index changes to a new playlist item.
* This event occurs before the player begins playing the new playlist item.
*
* Check if the playlist has been modified.
* If yes, load the modified playlist then play the index, where it should be.
* Otherwise, do nothing.
*/
function (evt) {
if (playlistIsModified) {
var playlistIndex = -1; // Error state.
if ((evt.index - lastIndex + 1) >= oldPlaylistLength) {
// Previous button on first item: play the last item of the playlist.
playlistIndex = playlist.length - 1;
} else if ((lastIndex - evt.index + 1) >= oldPlaylistLength) {
// Next button on last item: play the next item of the playlist.
playlistIndex = (findLastRecordedIndex() + 1) % playlist.length;
} else {
/**
* Find the playing index in the modified playlist.
* If it doesn't exist, take the next existing index.
*/
for (var i = 0; i < playlist.length && playlistIndex == -1; i++) {
if (playlist[i].oldIndex !== undefined && playlist[i].oldIndex >= evt.index) {
playlistIndex = i;
}
}
// If no index, take the first item.
if (playlistIndex < 0) {
playlistIndex = 0;
}
}
player.load(playlist);
player.playlistItem(lastIndex = playlistIndex);
return;
}
lastIndex = evt.index;
});
player.onComplete(
// Fired when an item completes playback.
function () {
if ((lastIndex + 1) >= oldPlaylistLength && playlistIsModified) {
// Playlist is completed (I don't use onPlaylistComplete, there were too many bugs) and modified.
var playlistIndex = (findLastRecordedIndex() + 1) % playlist.length;
if (playlistIndex > 0) {
// Playlist is no more completed: there are new elements at the end of the playlist.
player.load(playlist);
player.playlistItem(playlistIndex);
}
}
});
/**
* Find the last recorded index in the playlist.
*
* @returns {number} The last recorded in the playlist. If none, it returns -1.
*/
function findLastRecordedIndex() {
for (var i = playlist.length - 1; i > -1; i--) {
if (playlist[i].oldIndex !== undefined) {
return i;
}
}
return -1;
}
/**
* Join the playlist with other array(s).
*/
jwplayer.plugins.playlist_concat = function () {
// The arrays to add to the end of the playlist.
var arrays = Array.prototype.slice.call(arguments);
for (var i = 0; i < arrays.length; i++) {
for (var j = 0; j < arrays[i].length; j++) {
// Delete the oldIndex in each item, in case they are duplicated.
arrays[i][j].oldIndex = undefined;
}
playlist = playlist.concat(arrays[i]);
}
playlistIsModified = true;
// console.log(playlist);
};
/**
* Returns the player's modified playlist array.
*
* @returns {Array} The player's modified playlist array.
*/
jwplayer.plugins.playlist_getPlaylist = function () {
return playlist;
};
/**
* Returns the playlist item object at the specified index.
* If the index is not specified, the currently playing item is returned.
*
* @param index {number} The playlist index.
*
* @returns {Object} The playlist item object.
*/
jwplayer.plugins.playlist_getPlaylistItem = function (index) {
if (index !== undefined) {
return playlist[index];
} else {
return player.getPlaylistItem();
}
};
/**
* Returns the index of the currently active item in the playlist.
*
* @returns {number} The index of the currently active item in the playlist, if not found, -1.
*/
jwplayer.plugins.playlist_getPlaylistIndex = function () {
var index = player.getPlaylistIndex(), playlistIndex = -1;
if (playlistIsModified) {
for (var i = 0; i < playlist.length && playlistIndex == -1; i++) {
if (playlist[i].oldIndex !== undefined) {
if (playlist[i].oldIndex == index) {
playlistIndex = i;
} else if (playlist[i].oldIndex > index) {
break;
}
}
}
} else {
playlistIndex = index;
}
return playlistIndex;
};
/**
* Append the given items to the end of the playlist.
*/
jwplayer.plugins.playlist_push = function () {
// The items to add to the end of the array.
var items = Array.prototype.slice.call(arguments);
for (var i = 0; i < items.length; i++) {
// Delete the oldIndex in each item, in case they are duplicated.
items[i].oldIndex = undefined;
}
playlist = playlist.concat(items);
playlistIsModified = true;
// console.log(playlist);
};
/**
* Prepend the given items to the start of the playlist.
*/
jwplayer.plugins.playlist_shift = function () {
var _playlist;
// The items to add to the start of the array.
var items = Array.prototype.slice.call(arguments);
for (var i = 0; i < items.length; i++) {
// Delete the oldIndex in each item, in case they are duplicated.
items[i].oldIndex = undefined;
}
_playlist = playlist;
playlist = items.concat(_playlist);
playlistIsModified = true;
// console.log(playlist);
};
/**
* Reload the playlist if modified.
*/
jwplayer.plugins.playlist_reloadPlaylist = function () {
if (playlistIsModified) {
player.load(playlist);
}
};
/**
* Add new items while removing old items.
*
* @param index {number} The index at which to start changing the array.
* @param howMany {number} The number of old array items to remove. If howMany is 0, no items are removed. If howMany is greater than the number of items left in the array starting at index or isn't specified, then all of the items through the end of the array will be deleted.
*/
jwplayer.plugins.playlist_splice = function (index, howMany) {
if (index < 0) {
// If negative, will begin that many items from the end.
index += playlist.length;
} else if (index >= playlist.length) {
// If greater than the length of the array, actual starting index will be set to the length of the array.
index = playlist.length;
}
// The items to add to the array.
// If you don't specify any items, splice simply removes items from the array.
var items = Array.prototype.slice.call(arguments, 2);
if (isNaN(howMany)) {
items = Array.prototype.concat(howMany, items);
howMany = playlist.length;
}
for (var i = 0; i < items.length; i++) {
// Delete the oldIndex in each item, in case they are duplicated.
items[i].oldIndex = undefined;
}
playlist = playlist.slice(0, index).concat(items, playlist.slice(index + howMany));
playlistIsModified = true;
// console.log(playlist);
};
};
jwplayer().registerPlugin('jwplayer.playlist', '6.0', template);
})(jwplayer);