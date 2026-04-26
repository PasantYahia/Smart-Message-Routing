// ===== DATA STRUCTURES =====
let queue = []; // Priority Queue (sorted by priority)
let stack = []; // Stack (last sent messages)

// ===== ADD MESSAGE (ENQUEUE) =====
function addMessage() {
    const id = parseInt(document.getElementById('msgId').value);
    const priority = parseInt(document.getElementById('msgPriority').value);
    const text = document.getElementById('msgText').value.trim();
    const errorDiv = document.getElementById('formError');

    // Validation
    if (!id || isNaN(id)) {
        errorDiv.textContent = '[!] Please enter a valid ID.';
        return;
    }
    if (queue.find(m => m.id === id)) {
        errorDiv.textContent = '[!] This ID already exists. Try another.';
        return;
    }
    if (!text) {
        errorDiv.textContent = '[!] Message content cannot be empty.';
        return;
    }

    errorDiv.textContent = '';

    // Add to queue
    queue.push({ id, priority, text });

    // Sort by priority (1 = highest)
    queue.sort((a, b) => a.priority - b.priority);

    // Clear inputs
    document.getElementById('msgId').value = '';
    document.getElementById('msgText').value = '';
    document.getElementById('msgPriority').value = '1';

    renderQueue();
}

// ===== SEND MESSAGE (DEQUEUE) =====
function sendMessage() {
    if (queue.length === 0) {
        alert('No messages in queue!');
        return;
    }

    const sent = queue.shift(); // Remove from front (highest priority)
    stack.push(sent);           // Push to stack

    renderQueue();
    renderStack();
}

// ===== PEEK =====
function peekMessage() {
    if (queue.length === 0) {
        alert('No messages in queue!');
        return;
    }

    // Highlight the first item
    const items = document.querySelectorAll('.message-item');
    if (items.length > 0) {
        items[0].classList.add('peek-highlight');
        setTimeout(() => items[0].classList.remove('peek-highlight'), 2000);
    }
}

// ===== DELETE =====
function deleteMessage(id) {
    queue = queue.filter(m => m.id !== id);
    renderQueue();
}

// ===== EDIT =====
function openEdit(id) {
    const msg = queue.find(m => m.id === id);
    if (!msg) return;

    document.getElementById('editId').value = id;
    document.getElementById('editText').value = msg.text;
    document.getElementById('editPriority').value = msg.priority;
    document.getElementById('editModal').classList.remove('hidden');
}

function saveEdit() {
    const id = parseInt(document.getElementById('editId').value);
    const newText = document.getElementById('editText').value.trim();
    const newPriority = parseInt(document.getElementById('editPriority').value);

    if (!newText) {
        alert('Content cannot be empty!');
        return;
    }

    // Update message
    queue = queue.map(m => m.id === id ? { ...m, text: newText, priority: newPriority } : m);

    // Re-sort
    queue.sort((a, b) => a.priority - b.priority);

    closeModal();
    renderQueue();
}

function closeModal() {
    document.getElementById('editModal').classList.add('hidden');
}

// ===== RENDER QUEUE =====
function renderQueue() {
    const list = document.getElementById('queueList');
    const empty = document.getElementById('queueEmpty');

    if (queue.length === 0) {
        empty.style.display = 'block';
        list.innerHTML = '';
        return;
    }

    empty.style.display = 'none';

    list.innerHTML = queue.map(msg => `
        <div class="message-item">
            <div class="priority-badge p${msg.priority}">${msg.priority}</div>
            <div class="msg-info">
                <div class="msg-id">ID: ${msg.id}</div>
                <div class="msg-text">${msg.text}</div>
            </div>
            <div class="msg-actions">
                <button class="btn-icon edit" onclick="openEdit(${msg.id})" title="Edit">✏️</button>
                <button class="btn-icon del" onclick="deleteMessage(${msg.id})" title="Delete">🗑</button>
            </div>
        </div>
    `).join('');
}

// ===== RENDER STACK =====
function renderStack() {
    const display = document.getElementById('stackDisplay');

    if (stack.length === 0) {
        display.innerHTML = '<div class="empty-state">No messages sent yet</div>';
        return;
    }

    const last = stack[stack.length - 1]; // Top of stack
    display.innerHTML = `
        <div class="stack-item">
            <div class="stack-label">▲ LAST SENT</div>
            <div class="stack-id">ID: ${last.id} &nbsp;|&nbsp; Priority: ${last.priority}</div>
            <div class="stack-text">${last.text}</div>
        </div>
    `;
}

// Close modal on outside click
document.getElementById('editModal').addEventListener('click', function(e) {
    if (e.target === this) closeModal();
});
